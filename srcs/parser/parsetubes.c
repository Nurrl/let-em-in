/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetubes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:46:02 by lroux             #+#    #+#             */
/*   Updated: 2019/01/23 18:58:56 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool	linkrooms(t_lemin *lemin, char *room1, char *room2, t_rooms *rooms)
{
	t_room	*node;
	int		id1;
	int		id2;

	id1 = -1;
	id2 = -1;
	node = rooms->head;
	while (node)
	{
		if (ft_strequ(node->name, room1))
			id1 = node->id;
		if (ft_strequ(node->name, room2))
			id2 = node->id;
		node = node->next;
	}
	free(room1);
	free(room2);
	if (id1 == -1 || id2 == -1 || (id1 == id2))
		return (false);
	lemin->tubes[id1][id2] = true;
	lemin->tubes[id2][id1] = true;
	return (true);
}

t_bool	maketubes(t_lemin *lemin, t_rooms *rooms, char *line)
{
	if (!(lemin->tubes = (int**)ft_mk2array(
			lemin->roomcount, lemin->roomcount, sizeof(**lemin->tubes))))
		return (false);
	while (true)
	{
		if (line[0] != '#')
		{
			if (ft_cc(line, '-') != 1
					|| ft_strchr(line, '-')[1] == 0)
				break ;
			if (!linkrooms(lemin,
					ft_strndup(line, ft_strchr(line, '-') - line),
					ft_strdup(ft_strchr(line, '-') + 1),
					rooms))
				break ;
		}
		if (keepgnl(stdin, &line, lemin) < 1)
			break ;
	}
	return (true);
}
