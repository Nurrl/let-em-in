/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:04:26 by lroux             #+#    #+#             */
/*   Updated: 2019/01/31 15:10:48 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_bool	parseants(t_lemin *lemin)
{
	char *line;

	if (keepgnl(stdin, &line, lemin) < 1 || !ft_strisdigit(line))
		return (false);
	errno = 0;
	lemin->antcount = ft_strtoll(line, NULL, 10);
	if (errno == EINVAL || errno == ERANGE || lemin->antcount < 1)
		return (false);
	return (true);
}

int				keepgnl(const int fd, char **line, t_lemin *lemin)
{
	int		rt;
	t_line	*cur;

	if ((rt = gnl(fd, line)) == 0)
		return (0);
	if (!(cur = ft_calloc(1, sizeof(*cur))))
		return (-1);
	cur->line = *line;
	if (!lemin->kr.lines)
	{
		lemin->kr.lines = cur;
		lemin->kr.lend = cur;
	}
	else
	{
		lemin->kr.lend->next = cur;
		lemin->kr.lend = cur;
	}
	return (rt);
}

static	t_bool	roomstoarray(t_lemin *lemin, t_rooms *rooms)
{
	t_room *node;

	if (!(lemin->rooms = ft_calloc(lemin->roomcount, sizeof(*lemin->rooms))))
		return (false);
	node = rooms->head;
	while (node)
	{
		lemin->rooms[node->id] = *node;
		node = node->next;
	}
	if (!rooms->start || !rooms->end)
		return (false);
	lemin->startid = rooms->start->id;
	lemin->endid = rooms->end->id;
	return (true);
}

t_bool			parser(t_lemin *lemin)
{
	t_rooms	rooms;

	rooms = (t_rooms){0, 0, 0, 0};
	if (!parseants(lemin))
		return (false);
	if (!parserooms(lemin, &rooms))
		return (false);
	return (roomstoarray(lemin, &rooms));
}
