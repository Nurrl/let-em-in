/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/02/09 07:05:04 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_bool filter(t_lemin *lemin, int prev, int curr, int next)
{
	if (!lemin->tubes[curr][next])
		return (false);
	if (!lemin->flowvisited[next]
			&& lemin->flows[curr][next] < 1)
		return (true);
	else if (lemin->flowvisited[next] && !lemin->flowvisited[prev]
			&& lemin->flows[curr][next] == -1)
		return (true);
	else if (lemin->flowvisited[next] && lemin->flowvisited[prev]
			&& lemin->flows[curr][next] < 1)
		return (true);
	else
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
			parents[lemin->rooms[next].id] = lemin->rooms[curr].id;
//			printpath(lemin, newpath);
			ll_add(q, (void*)&lemin->rooms[next]);
			visited[next] = true;
		}
	}
}

void	printparentspath(t_lemin *lemin, int *parents)
{
	int id;

	id = lemin->endid;
	while (id != lemin->startid)
	{
		ft_printf("%d > ", id);
		id = parents[id];
	}
	ft_printf("%d", id);
	ft_printf("\n");

}

t_node	*pathfromparents(t_lemin *lemin, int *parents)
{
	t_node *path;
	int id;

	path = NULL;
	id = lemin->endid;
	while (id != lemin->startid)
	{
		ll_addfront(&path, &lemin->rooms[id]);
		ft_printf("%d > ", id);
		id = parents[id];
	}
	ft_printf("%d", id);
	ft_printf("\n");
	return (path);
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
			free(parents);
			free(visited);
			return (pathfromparents(lemin, parents));
		}
		updatequeue(lemin, &q, room, visited, parents);
		/* TODO: Free path */
	}
	return (NULL);
}
