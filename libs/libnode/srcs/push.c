/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:32:46 by lroux             #+#    #+#             */
/*   Updated: 2019/01/22 16:48:32 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnode.h"

void	nd_pushhead(t_nodes *list, void *data)
{
	t_node *node;

	if (!list || !data || !(node = ft_calloc(1, sizeof(*node))))
		return ;
	list->size++;
	node->data = data;
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->next = list->head;
		list->head = node;
	}
}

void	nd_pushtail(t_nodes *list, void *data)
{
	t_node *node;

	if (!list || !data || !(node = ft_calloc(1, sizeof(*node))))
		return ;
	list->size++;
	node->data = data;
	if (!list->tail)
	{
		list->tail = node;
		list->head = node;
	}
	else
	{
		node->prev = list->tail;
		list->tail = node;
	}
}
