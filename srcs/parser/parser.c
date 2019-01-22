/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:04:26 by lroux             #+#    #+#             */
/*   Updated: 2019/01/22 14:04:14 by lroux            ###   ########.fr       */
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

	rt = gnl(fd, line);
	if (!(cur = ft_calloc(1, sizeof(*cur))))
		return (-1);
	cur->line = *line;
	if (!lemin->lines)
	{
		lemin->lines = cur;
		lemin->lend = cur;
	}
	else
	{
		lemin->lend->next = cur;
		lemin->lend = cur;
	}
	return (rt);
}

t_bool			parser(t_lemin *lemin)
{
	if (!parseants(lemin))
		return (false);
	if (!parserooms(lemin))
		return (false);
	return (true);
}
