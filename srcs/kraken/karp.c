/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:23:33 by glodi             #+#    #+#             */
/*   Updated: 2019/02/24 18:19:46 by lroux            ###   ########.fr       */
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
	if (parents[id] == lemin->startid)
		lemin->kr.isstartend = true;
	while (id != lemin->startid)
	{
		lemin->flows[id][parents[id]] -= 1;
		lemin->flows[parents[id]][id] += 1;
		id = parents[id];
	}
	return (true);
}

void			freepacket(t_node **packet)
{
	t_node *tmp;
	t_node *path;

	if (!packet || !*packet)
		return ;
	tmp = *packet;
	while (true)
	{
		path = tmp->data;
		ll_del(&path);
		tmp = tmp->next;
		if (tmp == *packet)
			break ;
	}
	ll_del(packet);
}

t_node			*karp(t_lemin *lemin,
		t_bool (*evalpacket)(t_lemin *lemin, t_node *packet, t_node *best))
{
	t_node	*best;
	t_node	*current;
	int		*parents;

	best = NULL;
	if (!(lemin->flows = (int **)ft_mk2array(lemin->roomcount,
				lemin->roomcount, sizeof(**lemin->flows)))
		|| !(parents = malloc(lemin->roomcount * sizeof(*parents))))
		return (NULL);
	while (!lemin->kr.isstartend
			&& applyflow(lemin, parents, bfs(lemin, parents)))
	{
		current = extractpaths(lemin);
		if (evalpacket(lemin, current, best))
		{
			freepacket(&best);
			best = current;
		}
		else
			freepacket(&current);
	}
	free(parents);
	return (best);
}
