/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:23:33 by glodi             #+#    #+#             */
/*   Updated: 2019/02/11 18:22:01 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_node	*setpath(t_lemin *lemin, int pos, t_node *path)
{
	int	i;

	if (pos == lemin->endid)
		return (path);
	i = -1;
	while (++i < lemin->roomcount && lemin->flows[pos][i] != 1)
		;
	ll_add(&path, &lemin->rooms[i]);
	return (setpath(lemin, i, path));
}

static t_node	*extractpaths(t_lemin *lemin)
{
	int		i;
	t_node	*path;
	t_node	*batchpaths;

	batchpaths = NULL;
	i = -1;
	while (++i < lemin->roomcount)
	{
		if (lemin->flows[lemin->startid][i] == 1)
		{
			path = NULL;
			ll_add(&path, &lemin->rooms[lemin->startid]);
			ll_add(&path, &lemin->rooms[i]);
			path = setpath(lemin, i, path);
			ll_add(&batchpaths, path);
		}
	}
	return (batchpaths);
}

static t_bool	applyflow(t_lemin *lemin, int *parents, t_bool success)
{
	int id;

	if (!success)
		return (false);
	id = lemin->endid;
	while (id != lemin->startid)
	{
		ft_printf("%d {green}<<{eoc} ", id);
		lemin->flows[id][parents[id]] -= 1;
		lemin->flows[parents[id]][id] += 1;
		id = parents[id];
	}
	ft_printf("%d\n", id);
	//printmatrix(lemin->flows, lemin->roomcount);
	return (true);
}

t_node			*karp(t_lemin *lemin,
		t_bool (*evalpacket)(t_lemin *lemin, t_node *packet, t_node *best))
{
	int		i;
	t_node	*best;
	t_node	*current;
	int		*parents;

	best = NULL;
	if (!(lemin->flows = (int **)ft_mk2array(lemin->roomcount,
				lemin->roomcount, sizeof(**lemin->flows)))
		|| !(parents = malloc(lemin->roomcount * sizeof(*parents))))
		return (NULL);
	while (applyflow(lemin, parents, bfs(lemin, parents)))
	{
		// printmatrix(lemin->flows, lemin->roomcount);
		current = extractpaths(lemin);
//		ft_printf("Packet: ({red}%p{eoc})\n", current);
		checkduplicate(lemin, current);
		//printpacket(lemin, current);
		if (evalpacket(lemin, current, best))
			best = current;
	}
	i = -1;
	while (++i < lemin->roomcount)
		free(lemin->flows[i]);
	free(lemin->flows);
	lemin->flows = NULL;
	return (best);
}
