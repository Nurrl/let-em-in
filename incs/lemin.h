/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:57:07 by lroux             #+#    #+#             */
/*   Updated: 2019/01/31 15:09:29 by lroux            ###   ########.fr       */
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

typedef struct	s_kraken {
	float		bestflow;

	t_line		*lines;
	t_line		*lend;
}				t_kraken;

typedef struct	s_lemin {
	int			antcount;

	int			roomcount;
	t_room		*rooms;
	int			startid;
	int			endid;

	int			**tubes;
	int			**flows;
	int			turns;

	t_kraken	kr;
}				t_lemin;

/*
** Parsing functions
*/

t_bool			parser(t_lemin *lemin);
t_bool			parserooms(t_lemin *lemin, t_rooms *rooms);
t_bool			maketubes(t_lemin *lemin, t_rooms *rooms, char *line);
int				keepgnl(const int fd, char **line, t_lemin *lemin);

/*
** Kraken functions
*/

int				*bfs(t_lemin *lemin);
t_paths			*karp(t_lemin *l,
		t_bool (*evalpacket)(t_lemin *lemin, t_paths *packet, t_paths *best));
int				*initpath(int count, size_t size);

/*
** Collector functions
*/

t_bool			collectlines(t_line *lines);

#endif
