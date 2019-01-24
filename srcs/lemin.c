/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:35:48 by lroux             #+#    #+#             */
/*   Updated: 2019/01/24 15:12:33 by glodi            ###   ########.fr       */
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
	t_line	*lines;
	char	*l;

	while (keepgnl(stdin, &l, lemin) > 0)
		;
	lines = lemin->lines;
	while (lines)
	{
		if (lines->line)
			ft_printf("%s\n", lines->line);
		lines = lines->next;
	}
	collectlines(lemin->lines);
}

// TODO: Handle if there no start or no end
int			main(void)
{
	static t_lemin	lemin;
	int				*path;

	if (!parser(&lemin) && collectlines(lemin.lines))
		return (exiterr());
	if (!(path = bfs(&lemin)) && collectlines(lemin.lines))
		return (exiterr());
	printlines(&lemin);

// Debug
	int		i;
	// int		x;
	// int		y;
	// ft_printf("{red}---{eoc}\nAnts: %d, Rooms: %d.\n", lemin.antcount, lemin.roomcount);
	// i = -1;
	// while (++i < lemin.roomcount)
	// {
	// 	ft_printf("Id: %d, Name: %s, Pos: {%d, %d}\n", lemin.rooms[i].id,
	// 		lemin.rooms[i].name, lemin.rooms[i].x, lemin.rooms[i].y);
	// }
	// y = -1;
	// while (++y < lemin.roomcount && (x = -1) == -1)
	// {
	// 	while (++x < lemin.roomcount)
	// 		ft_printf("%d ", lemin.tubes[y][x]);
	// 	ft_printf("\n");
	// }
// Debug

	i = -1;
	ft_printf("[");
	while (path[++i] != -1)
	{
		// ft_printf("%s", lemin.rooms[path[i]].name);
		// ft_printf("/");
		ft_printf("%d", path[i]);
		if (path[i+1] != -1)
			ft_printf(", ", path[i]);
	}
	ft_printf("]\n");
	ft_memdel(&path);
	/* Clear the structure (free) */
	return (0);
}
