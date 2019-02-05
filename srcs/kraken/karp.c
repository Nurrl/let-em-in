/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:23:33 by glodi             #+#    #+#             */
/*   Updated: 2019/02/06 00:25:42 by glodi            ###   ########.fr       */
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
	ll_add(&path, (t_data)i);
	return (setpath(lemin, f, i, path));
}

static t_node	*extractpaths(t_lemin *lemin, int **f)
{
	int		i;
	t_node	*path;
	t_node	*batchpaths;

	printmatrix(f, lemin->roomcount);

	i = -1;
	while (++i < lemin->roomcount)
	{
		if (f[lemin->startid][i] == 1)
		{
			ll_add(&path, (t_data)lemin->startid);
			ll_add(&path, (t_data)i);
			path = setpath(lemin, f, i, path);
			ll_add(&batchpaths, (t_data)(void *)path);
		}
	}
	return (batchpaths);
}

static t_bool	applyflow(t_lemin *lemin, t_node *path)
{
	int		curr;
	int		next;

	printpath(lemin, path);
	curr = ll_pop(&path, 0).i;
	while ((next = ll_pop(&path, 0).i))
	{
		lemin->flows[next][curr] -= 1;
		lemin->flows[curr][next] += 1;
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
	if (!(l->flows = (int **)ft_mk2array(
			l->roomcount, l->roomcount, sizeof(**l->flows))))
		return (NULL);
	while (applyflow(l, bfs(l)))
	{
		ft_printf("Packet: ({red}%p{eoc})\n", l);
		current = extractpaths(l, l->flows);
//		checkduplicate(l, current);
		if (evalpacket(l, current, best))
			best = current;
		//bprintmatrix(l, l->flows, l->roomcount);
	}
	i = -1;
	while (++i < l->roomcount)
		free(l->flows[i]);
	free(l->flows);
	l->flows = NULL;
	return (best);
}
