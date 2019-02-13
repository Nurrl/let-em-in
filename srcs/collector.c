/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 18:00:44 by lroux             #+#    #+#             */
/*   Updated: 2019/02/13 21:59:36 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	cleanrooms(t_room **rooms, int size)
{
	t_room *list;

	list = *rooms;
	while (--size > -1)
		free(list[size].name);
	free(*rooms);
	*rooms = NULL;
}

static void	cleanwater(int ***array, int size)
{
	while (--size > -1)
		free((*array)[size]);
	free(*array);
	*array = NULL;
}

t_bool		cleanlemin(t_lemin *lemin)
{
	if (lemin->rooms)
		cleanrooms(&lemin->rooms, lemin->roomcount);
	if (lemin->tubes)
		cleanwater(&lemin->tubes, lemin->roomcount);
	if (lemin->flows)
		cleanwater(&lemin->flows, lemin->roomcount);
	if (lemin->lines)
		printlines(lemin, false);
	return (true);
}

void		cleanpacket(t_node **packet)
{
	t_node *path;

	while ((path = ll_pop(packet, 0)))
		ll_del(&path);
	*packet = NULL;
}

t_bool		cleanroomlist(t_rooms *rooms)
{
	t_room *node;
	t_room *cur;

	cur = rooms->head;
	while (cur)
	{
		node = cur;
		cur = cur->next;
		free(node->name);
		free(node);
	}
	return (false);
}
