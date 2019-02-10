/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/02/10 04:13:22 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_node	*pathfromparents(t_lemin *lemin, int *parents)
{
	t_node *path;
	int id;

	path = NULL;
	id = lemin->endid;
	while (id != lemin->startid)
	{
		ll_addfront(&path, &lemin->rooms[id]);
//		ft_printf("%s > ", lemin->rooms[id].name);
		id = parents[id];
	}
//	ft_printf("%s", lemin->rooms[id].name);
//	ft_printf("\n");
	if (id == lemin->startid)
		ll_addfront(&path, &lemin->rooms[id]);
	return (path);
}

static t_bool filter(t_lemin *l, int prev, int curr, int next)
{
	if (!l->tubes[curr][next])
		return (false);
	if (l->flows[prev][curr] == -1 && l->flows[curr][next] < 1)
		return (true);
	else if (l->flows[prev][curr] == 0 && l->flows[curr][next] < 1)
		return (true);
	return (false);

}

static void	updatequeue(t_lemin *lemin, t_node **q,
		t_room *room, t_bool *visited, int *parents)
{
	int		prev;
	int		next;
	int		curr;

	curr = room->id;
	prev = parents[curr];
	next = -1;
	while (++next < lemin->roomcount)
	{
		if (!visited[next] && filter(lemin, prev, curr, next))
		{
			ll_add(q, &lemin->rooms[next]);
			parents[lemin->rooms[next].id] = lemin->rooms[curr].id;
			visited[next] = true;
		}
	}
}

/*
** The value returned will have lemin->roomcount size
** and all value unitialized will be set to -1
*/
t_node		*bfs(t_lemin *lemin)
{
	t_node	*q;
	t_room	*room;
	t_bool	*visited;
	int		*parents;

	if (!(parents = ft_calloc(lemin->roomcount, sizeof(parents))))
		return (NULL);
	if (!(visited = ft_calloc(lemin->roomcount, sizeof(*visited))))
		return (NULL);
	q = 0;
	ll_add(&q, &lemin->rooms[lemin->startid]);
	visited[lemin->startid] = true;
	while ((room = ll_pop(&q, 0)))
	{
		if (room->id == lemin->endid)
		{
			/* TODO: Free queue */
			free(visited);
			return (pathfromparents(lemin, parents));
		}
		updatequeue(lemin, &q, room, visited, parents);
		/* TODO: Free path */
	}
	return (NULL);
}
