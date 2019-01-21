/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:35:48 by lroux             #+#    #+#             */
/*   Updated: 2019/01/21 19:29:59 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	exiterr(void)
{
	ft_printf("ERROR\n");
	return (1);
}

static void	printlines(t_lemin *lemin)
{
	t_line	*line;
	char	*l;

	while (keepgnl(stdin, &l, lemin) > 0)
		;;
	line = lemin->lines;
	while (line->next)
	{
		ft_printf("%s\n", line->line);
		line =line->next;
	}
	collectlines(lemin->lines);
}

int			main(void)
{
	static t_lemin	lemin;

	if (!parser(&lemin) && collectlines(lemin.lines))
		return (exiterr());
	printlines(&lemin);

// Debug
	t_room	*room;
	int		x;
	int		y;
	ft_printf("{red}---{eoc}\nAnts: %d, Rooms: %d.\n", lemin.antcount, lemin.roomcount);
	room = lemin.rooms.head;
	while (room)
	{
		ft_printf("Id: %d, Name: %s, Pos: {%d, %d}\n", room->id,
			room->name, room->x, room->y);
		room = room->next;
	}
	y = -1;
	while (++y < lemin.roomcount && (x = -1) == -1)
	{
		while (++x < lemin.roomcount)
			ft_printf("%2d ", lemin.tubes[y][x]);
		ft_printf("\n");
	}
// Debug

	/* Clear the structure (free) */
	return (0);
}
