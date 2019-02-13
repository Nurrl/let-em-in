/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/02/13 22:08:09 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_bool	isflowing(t_lemin *lemin, int current)
{
	int i;

	if (current == lemin->startid)
		return (false);
	i = -1;
	while (++i < lemin->roomcount)
		if (lemin->flows[current][i] != 0)
			return (true);
	return (false);
}

static t_bool	filter(t_lemin *lemin, int *parents, int current, int neigh)
{
	int prev;

	prev = parents[current];
	if (lemin->flows[current][neigh] == 1)
		return (false);
	if (lemin->flows[current][neigh] == 0
			&& prev != -1
			&& lemin->flows[current][prev] == 0
			&& isflowing(lemin, current))
		return (false);
	return (true);
}

static t_bool	doprocess(t_lemin *lemin,
		t_node *q, t_bool *visited, int *parents)
{
	t_room	*room;
	int		i;

	while ((room = ll_pop(&q, 0)))
	{
		i = -1;
		while (++i < lemin->roomcount)
		{
			if (lemin->tubes[room->id][i] && !visited[i]
				&& filter(lemin, parents, room->id, i))
			{
				visited[i] = true;
				parents[i] = room->id;
				ll_add(&q, &lemin->rooms[i]);
				if (i == lemin->endid)
				{
					ll_del(&q);
					free(visited);
					return (true);
				}
			}
		}
	}
	free(visited);
	return (false);
}

t_bool			bfs(t_lemin *lemin, int *parents)
{
	t_bool	*visited;
	t_node	*q;

	ft_memset(parents, -1, lemin->roomcount * sizeof(*parents));
	if (!(visited = ft_calloc(lemin->roomcount, sizeof(*visited))))
		return (false);
	q = 0;
	visited[lemin->startid] = true;
	ll_add(&q, &lemin->rooms[lemin->startid]);
	return (doprocess(lemin, q, visited, parents));
}
