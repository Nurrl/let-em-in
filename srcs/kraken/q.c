/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:38:21 by glodi             #+#    #+#             */
/*   Updated: 2019/01/24 15:21:30 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	q_append(t_paths *q, int *path)
{
	t_path *node;

	if (!q || !(node = ft_calloc(1, sizeof(*node))))
		return ;
	node->path = path;
	if (q->tail)
		q->tail->next = node;
	else
		q->head = node;
	q->tail = node;
}

int		*q_pophead(t_paths *q)
{
	t_path	*node;
	int		*path;

	if (!q || !q->head)
		return (NULL);
	node = q->head;
	q->head = q->head->next;
	if (!q->head)
		q->tail = NULL;
	path = node->path;
	ft_memdel((void **)&node);
	return (path);
}

void	q_destroy(t_paths *q)
{
	t_path	*tmp;
	t_path	*next;

	tmp = q->head;
	while (tmp)
	{
		ft_memdel((void *)&tmp->path);
		next = tmp->next;
		ft_memdel((void **)&tmp);
		tmp = next;
	}
	q = NULL;
}
