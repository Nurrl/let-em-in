/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/02/11 03:53:50 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_bool	isflowing(t_lemin *lemin, int current)
{
	int i;

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
			&& lemin->flows[current][prev] == 0
			&& isflowing(lemin, current))
		return (false);
	return (true);
}

t_bool			bfs(t_lemin *lemin, int *parents)
{
	t_bool	*visited;
	t_room	*room;
	t_node	*q;
	int		i;

	parents[lemin->startid] = -1;
	if (!(visited = ft_calloc(lemin->roomcount, sizeof(*visited))))
		return (false);
	q = 0;
	ll_add(&q, &lemin->rooms[lemin->startid]);
	while ((room = ll_pop(&q, 0)) && (i = -1) == -1)
	{
		while (++i < lemin->roomcount)
		{
			if (lemin->tubes[room->id][i] && !visited[i]
				&& filter(lemin, parents, room->id, i))
			{
				visited[i] = true;
				parents[i] = room->id;
				ll_add(&q, &lemin->rooms[i]);
				if (i == lemin->endid)
					return (true);
			}
		}
	}
	return (false);
}
