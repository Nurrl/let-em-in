/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kraken.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:32:09 by glodi             #+#    #+#             */
/*   Updated: 2019/01/25 15:12:41 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KRAKEN_H
# define KRAKEN_H

typedef struct	s_path t_path;
typedef struct	s_paths t_paths;

typedef struct	s_paths {
	t_path *tail;
	t_path *head;
}				t_paths;

typedef struct	s_path {
	int		*path;
	t_path	*next;
}				t_path;

void	q_append(t_paths *q, int *path);
int		*q_pophead(t_paths *q);
void	q_destroy(t_paths *q);

#endif
