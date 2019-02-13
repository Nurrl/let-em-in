/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 19:13:35 by glodi             #+#    #+#             */
/*   Updated: 2019/02/13 20:02:25 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	printpath(t_lemin *l, t_node *path)
{
	t_node *curr;

	curr = path;
	while (true)
	{
		if (((t_room*)curr->data)->id == l->startid)
			ft_dprintf(stderr, "{green}");
		if (((t_room*)curr->data)->id == l->endid)
			ft_dprintf(stderr, "{red}");
		ft_dprintf(stderr, " %s{eoc}", ((t_room*)curr->data)->name);
		curr = curr->next;
		if (curr == path)
			break ;
		ft_dprintf(stderr, " >");
	}
	ft_dprintf(stderr, "\n");
}

void	printpacket(t_lemin *l, t_node *packet)
{
	t_node *curr;

	curr = packet;
	ft_dprintf(stderr, "Packet: ({red}%p{eoc})\n", packet);
	while (true)
	{
		ft_dprintf(stderr, "\t{lightmagenta}%p{eoc}: ", curr->data);
		ft_dprintf(stderr, "({lightblue}%d{eoc})", ll_len(curr->data));
		printpath(l, curr->data);
		curr = curr->next;
		if (curr == packet)
			break ;
	}
}
