/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:45:58 by lroux             #+#    #+#             */
/*   Updated: 2019/01/22 17:43:57 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnode.h"

void	*nd_pophead(t_nodes *list)
{
	return (nd_pop(list, 0));
}

void	*nd_poptail(t_nodes *list)
{
	return (nd_pop(list, -1));
}

void	*nd_pop(t_nodes *list, size_t index)
{
	void	*data;
	t_node	*node;

	node = ((index > -1) ? list->head : list->tail);
	index = ((index > -1) ? index : -index - 1);
	while (index--)
	{
		node = (index > -1) ? node->next : node->prev;
		if (!node)
			return (NULL);
	}
	data = node->data;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node);
	return (data);
}
