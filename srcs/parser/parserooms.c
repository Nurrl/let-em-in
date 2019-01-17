/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:45:56 by lroux             #+#    #+#             */
/*   Updated: 2019/01/17 14:45:07 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

#define END 1
#define START 2

static t_bool	parsecommand(char **line, int *flags)
{
	*flags = 0;
	if ((*line)[0] == '#' && (*line)[1] == '#')
	{
		if (ft_strequ(*line + 2, "start"))
			*flags = START;
		else if (ft_strequ(*line + 2, "end"))
			*flags = END;
		free(*line);
		if (gnl(stdin, line) < 1)
			return (false);
	}
	return (true);
}

static t_bool	createroom(char *line, int flags, t_lemin *lemin)
{
	t_room	*room;

	if (!(room = ft_calloc(1, sizeof(*room))))
		return (false);
	room->id = lemin->roomcount++;
	room->name = ft_strndup(line, ft_strebrk(line, "\t\n\v\f\r ") - line);
	room->x = ft_strtoll(line
			+ ft_strlen(room->name) + 1, NULL, 10);
	room->y = ft_strtoll(line
			+ ft_strlen(room->name) + 1 + ft_intlen(room->x, 10) + 1, NULL, 10);
	if (!lemin->rooms.head)
	{
		lemin->rooms.head = room;
		lemin->rooms.tail = room;
	}
	else
	{
		lemin->rooms.tail->next = room;
		lemin->rooms.tail = room;
	}
	if (flags == START)
		lemin->rooms.start = room;
	else if (flags == END)
		lemin->rooms.end = room;
	return (true);
}

t_bool			parserooms(t_lemin *lemin)
{
	char	*line;
	int		flags;

	while (gnl(stdin, &line) > 0)
	{
		if (!parsecommand(&line, &flags))
			return (false);
		if (line[0] == '#' && collect(line) == false)
			continue ;
		if (ft_cw(line) != 3)
			break ;
		if (line[0] == 'L' || !createroom(line, flags, lemin))
			return (collect(line));
		free(line);
	}
	return (maketubes(lemin, line));
}
