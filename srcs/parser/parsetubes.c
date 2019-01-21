/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetubes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:46:02 by lroux             #+#    #+#             */
/*   Updated: 2019/01/21 19:19:28 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool	linkrooms(t_lemin *lemin, char *room1, char *room2)
{
	t_room	*node;
	int		id1;
	int		id2;

	id1 = -1;
	id2 = -1;
	node = lemin->rooms.head;
	while (node)
	{
		if (ft_strequ(node->name, room1))
			id1 = node->id;
		if (ft_strequ(node->name, room2))
			id2 = node->id;
		node = node->next;
	}
	if (id1 != -1 && id2 != -1)
	{
		lemin->tubes[id1][id2] = true;
		lemin->tubes[id2][id1] = true;
	}
	free(room1);
	free(room2);
	return (true);
}

t_bool	maketubes(t_lemin *lemin, char *line)
{
	if (!(lemin->tubes = (t_bool**)ft_mk2array(
			lemin->roomcount, lemin->roomcount, sizeof(**lemin->tubes))))
		return (false);
	while (true)
	{
		if (ft_cc(line, '-') != 1
				|| ft_strchr(line, '-')[1] == 0)
			break ;
		if (!linkrooms(lemin,
				ft_strndup(line, ft_strchr(line, '-') - line),
				ft_strdup(ft_strchr(line, '-') + 1)))
			return (false);
		if (keepgnl(stdin, &line, lemin) < 1)
			break ;
	}
	return (true);
}
