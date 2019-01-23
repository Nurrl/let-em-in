/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:57:07 by lroux             #+#    #+#             */
/*   Updated: 2019/01/23 16:47:28 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "kraken.h"
# include <libft.h>
# include <libpf.h>
# include <gnl.h>

typedef struct	s_line {
	char			*line;
	struct s_line	*next;
}				t_line;

typedef struct	s_room {
	int				id;
	char			*name;

	int				x;
	int				y;
	struct s_room	*next;
}				t_room;

typedef struct	s_rooms {
	t_room		*head;
	t_room		*tail;

	t_room		*start;
	t_room		*end;
}				t_rooms;

typedef struct	s_lemin {
	int			antcount;

	int			roomcount;
	t_room		*rooms; // Array of rooms
	int			startid;
	int			endid;

	int			**tubes;
	t_line		*lines;
	t_line		*lend;
}				t_lemin;

/*
** Parsing functions
*/

t_bool			parser(t_lemin *lemin);
t_bool			parserooms(t_lemin *lemin, t_rooms *rooms);
t_bool			maketubes(t_lemin *lemin, t_rooms *rooms, char *line);
int				keepgnl(const int fd, char **line, t_lemin *lemin);

/*
** Math functions
*/

int				*bfs(t_lemin *lemin);

/*
** Collector functions
*/

t_bool			collectlines(t_line *lines);

#endif
