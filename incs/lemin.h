/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:57:07 by lroux             #+#    #+#             */
/*   Updated: 2019/02/13 21:58:45 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "ll.h"
# include <libft.h>
# include <libpf.h>
# include <gnl.h>

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

	t_node		*lines;
	t_kraken	kr;
}				t_lemin;

typedef struct	s_ant {
	int			id;
	t_node		*pos;
}				t_ant;

/*
** TODO: typedef t_node t_path;
** TODO: typedef t_node t_packet;
*/

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

t_bool			bfs(t_lemin *lemin, int *parents);
t_node			*karp(t_lemin *l,
		t_bool (*evalpacket)(t_lemin *lemin, t_node *packet, t_node *best));
int				*initpath(int count, size_t size);

/*
** Print function
*/

void			printlines(t_lemin *lemin, t_bool print);
void			printants(t_lemin *lemin, t_node *packet);

/*
** Collector functions
*/

t_bool			cleanlemin(t_lemin *lemin);
void			cleanpacket(t_node **packet);
t_bool			cleanroomlist(t_rooms *rooms);

/*
** Debug functions
*/

void			printpath(t_lemin *l, t_node *path);
void			printpacket(t_lemin *l, t_node *paths);

#endif
