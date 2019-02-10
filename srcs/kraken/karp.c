/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:23:33 by glodi             #+#    #+#             */
/*   Updated: 2019/02/10 23:56:15 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_node	*setpath(t_lemin *lemin, int **f, int pos, t_node *path)
{
	int	i;

	if (pos == lemin->endid)
		return (path);
	i = -1;
	while (++i < lemin->roomcount && f[pos][i] != 1)
		;
	ll_add(&path, &lemin->rooms[i]);
	return (setpath(lemin, f, i, path));
}

static t_node	*extractpaths(t_lemin *lemin, int **f)
{
	int		i;
	t_node	*path;
	t_node	*batchpaths;

	batchpaths = NULL;
	i = -1;
	while (++i < lemin->roomcount)
	{
		if (f[lemin->startid][i] == 1)
		{
			path = NULL;
			ll_add(&path, &lemin->rooms[lemin->startid]);
			ll_add(&path, &lemin->rooms[i]);
			path = setpath(lemin, f, i, path);
			ll_add(&batchpaths, path);
		}
	}
	return (batchpaths);
}

static t_bool	applyflow(t_lemin *lemin, t_node *path)
{
	t_room *curr;
	t_room *next;

	if (!path)
		return (false);
	curr = ll_pop(&path, 0);
	while ((next = ll_pop(&path, 0)))
	{
		lemin->flows[next->id][curr->id] -= 1;
		lemin->flows[curr->id][next->id] += 1;
		// lemin->flowvisited[curr->id] = true;
		curr = next;
	}
	return (true);
}

t_node			*karp(t_lemin *l,
		t_bool (*evalpacket)(t_lemin *lemin, t_node *packet, t_node *best))
{
	int		i;
	t_node	*best;
	t_node	*current;

	best = NULL;
	if (!(l->flowvisited = ft_calloc(l->roomcount, sizeof(*l->flowvisited))))
		return (NULL);
	if (!(l->flows = (int **)ft_mk2array(
			l->roomcount, l->roomcount, sizeof(**l->flows))))
		return (NULL);
	while (applyflow(l, bfs(l)))
	{
		current = extractpaths(l, l->flows);
//		ft_printf("Packet: ({red}%p{eoc})\n", current);
		checkduplicate(l, current);
//		printpacket(l, current);
		if (evalpacket(l, current, best))
			best = current;
	}
	i = -1;
	while (++i < l->roomcount)
		free(l->flows[i]);
	free(l->flows);
	l->flows = NULL;
	return (best);
}
