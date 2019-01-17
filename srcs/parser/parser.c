/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:04:26 by lroux             #+#    #+#             */
/*   Updated: 2019/01/17 14:21:00 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_bool	parseants(t_lemin *lemin)
{
	char *line;

	if (gnl(stdin, &line) < 1 || !ft_strisdigit(line))
		return (collect(line));
	errno = 0;
	lemin->antcount = ft_strtoll(line, NULL, 10);
	free(line);
	if (errno == EINVAL || errno == ERANGE || lemin->antcount < 1)
		return (false);
	return (true);
}

t_bool			parser(t_lemin *lemin)
{
	t_room *room;

	if (!parseants(lemin))
		return (false);
	if (!parserooms(lemin))
		return (false);
	ft_printf("Ants: %d, Rooms: %d.\n", lemin->antcount, lemin->roomcount);
	room = lemin->rooms.head;
	while (room)
	{
		ft_printf("Id: %d, Name: %s, Pos: {%d, %d}\n", room->id,
			room->name, room->x, room->y);
		room = room->next;
	}
	return (true);
}
