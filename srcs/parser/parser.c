/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:04:26 by lroux             #+#    #+#             */
/*   Updated: 2019/02/13 22:01:30 by lroux            ###   ########.fr       */
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

	if ((rt = gnl(fd, line)) == 0)
		return (0);
	ll_add(&lemin->lines, *line);
	return (rt);
}

static	t_bool	roomstoarray(t_lemin *lemin, t_rooms *rooms)
{
	t_room *node;
	t_room *cur;

	if (!rooms->start || !rooms->end)
		return (cleanroomlist(rooms));
	lemin->startid = rooms->start->id;
	lemin->endid = rooms->end->id;
	if (!(lemin->rooms = ft_calloc(lemin->roomcount, sizeof(*lemin->rooms))))
		return (false);
	cur = rooms->head;
	while (cur)
	{
		node = cur;
		cur = cur->next;
		lemin->rooms[node->id] = *node;
		free(node);
	}
	return (true);
}

t_bool			parser(t_lemin *lemin)
{
	t_rooms	rooms;

	rooms = (t_rooms){0, 0, 0, 0};
	if (!parseants(lemin))
		return (false);
	if (!parserooms(lemin, &rooms))
		return (cleanroomlist(&rooms));
	return (roomstoarray(lemin, &rooms));
}
