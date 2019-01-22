/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:28:29 by lroux             #+#    #+#             */
/*   Updated: 2019/01/22 17:44:40 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnode.h"

void	*nd_gethead(t_nodes *list)
{
	return (nd_get(list, 0));
}

void	*nd_gettail(t_nodes *list)
{
	return (nd_get(list, -1));
}

void	*nd_get(t_nodes *list, size_t index)
{
	t_node	*node;

	node = ((index > -1) ? list->head : list->tail);
	index = ((index > -1) ? index : -index - 1);
	while (index--)
	{
		node = (index > -1) ? node->next : node->prev;
		if (!node)
			return (NULL);
	}
	return (node->data);
}
