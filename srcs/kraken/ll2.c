/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <lroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 20:04:04 by lroux             #+#    #+#             */
/*   Updated: 2019/02/13 20:04:22 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ll.h"

t_node	*ll_get(t_node *head, int id)
{
	t_bool	negative;
	t_node	*cur;

	if (!head)
		return (NULL);
	negative = false;
	if (id < 0)
		negative = true;
	if (negative)
		id = -id;
	cur = head;
	while (id--)
		cur = (negative) ? cur->prev : cur->next;
	return (cur);
}

void	*ll_pop(t_node **head, int id)
{
	void	*data;
	t_node	*cur;

	if (!head || !(cur = ll_get(*head, id)))
		return (NULL);
	data = cur->data;
	cur->next->prev = cur->prev;
	cur->prev->next = cur->next;
	if (cur->next == cur)
		*head = NULL;
	if (cur == *head)
		*head = cur->next;
	free(cur);
	return (data);
}

t_bool	ll_del(t_node **head)
{
	while (ll_pop(head, 0))
		;
	return (true);
}
