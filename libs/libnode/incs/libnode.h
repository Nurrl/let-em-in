/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libnode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:08:12 by lroux             #+#    #+#             */
/*   Updated: 2019/01/22 17:54:08 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBNODE_H
# define LIBNODE_H

# include <stdlib.h>
# include <libft.h>

/*
** Our actual linked list.
*/
struct					s_node {
	void			*data;

	struct s_node	*next;
	struct s_node	*prev;
};
typedef struct s_node	t_node;

/*
** The list being passed to the user.
*/
struct					s_nodes {
	size_t			size;

	struct s_node	*head;
	struct s_node	*tail;
};
typedef struct s_nodes	t_nodes;

/*
** Utils functions.
*/
t_nodes					nd_init(void *data);
void					nd_destroy(t_nodes *list);

void					nd_pushhead(t_nodes *list, void *data);
void					nd_pushtail(t_nodes *list, void *data);

void					*nd_pophead(t_nodes *list);
void					*nd_poptail(t_nodes *list);
void					*nd_pop(t_nodes *list, size_t index);

void					*nd_gethead(t_nodes *list);
void					*nd_gettail(t_nodes *list);
void					*nd_get(t_nodes *list, size_t index);

#endif
