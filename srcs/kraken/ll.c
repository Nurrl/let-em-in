/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:38:21 by glodi             #+#    #+#             */
/*   Updated: 2019/02/13 20:04:11 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ll.h"

void	ll_add(t_node **head, void *data)
{
	t_node *new;

	if (!(new = ft_calloc(1, sizeof(*new))))
		return ;
	new->data = data;
	if (!*head)
		new->next = new;
	else
		new->next = *head;
	if (!*head)
		new->prev = new;
	else
		new->prev = (*head)->prev;
	if (!*head)
		*head = new;
	(*head)->prev->next = new;
	(*head)->prev = new;
}

t_node	*ll_dup(t_node *head)
{
	t_node *dup;
	t_node *node;

	dup = 0;
	node = head;
	while (true)
	{
		ll_add(&dup, node->data);
		node = node->next;
		if (node == head)
			break ;
	}
	return (dup);
}

size_t	ll_len(t_node *head)
{
	size_t len;
	t_node *node;

	if (!head)
		return (0);
	len = 0;
	node = head;
	while (true)
	{
		len++;
		node = node->next;
		if (node == head)
			break ;
	}
	return (len);
}
