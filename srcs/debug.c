/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 19:13:35 by glodi             #+#    #+#             */
/*   Updated: 2019/02/10 04:13:24 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//
//void		bprintmatrix(t_lemin *l, int **f, int size)
//{
//	int i;
//	int y;
//
//	i = -1;
//	while (++i < size && (y = -1) == -1)
//	{
//		t_bool sw = false;
//
//		while (++y < size)
//			if (f[i][y])
//				sw = true;
//		if (sw)
//			ft_printf("(%s): ", l->rooms[i].name);
//		y = -1;
//		while (++y < size)
//		{
//			if (f[i][y])
//				ft_printf(" % d(`%s`)", f[i][y], l->rooms[y].name);
//		}
//		if (i == l->startid)
//			ft_printf(" <- start");
//		if (i == l->endid)
//			ft_printf(" <- end");
//		if (sw)
//			ft_printf("\n");
//	}
//}

void		printmatrix(int **f, int size)
{
	int i;
	int y;
	t_bool	boule;

	i = -1;
	while (++i < size && (y = -1) == -1)
	{
		boule = false;
		while (++y < size)
		{
			if (f[i][y] == -1)
			{
				ft_printf(" -1", f[i][y]);
				boule = true;
			}
			else if (f[i][y] == 1)
			{
				ft_printf("  1", f[i][y]);
				boule = true;
			}
//			else
//				ft_printf("  0", f[i][y]);
		}
		if (boule)
			ft_printf("\n");
	}
}

void		printpath(t_lemin *l, t_node *path)
{
	t_node *curr;

	curr = path;
	while (true)
	{
		//if (node->path[i] == l->startid)
		//	ft_printf("{green}");
		//if (node->path[i] == l->endid)
		//	ft_printf("{red}");
		ft_printf(" %s", ((t_room*)curr->data)->name);
		curr = curr->next;
		if (curr == path)
			break ;
		ft_printf(" >");
	}
	ft_printf("\n");
}

void	checkduplicate(t_lemin *l, t_node *packet)
{
	int		*seen = calloc(l->roomcount, sizeof(*seen));
	t_node	*packet_tmp;
	t_node	*room;
	t_room	*r;

	packet_tmp = packet;
	if (!packet)
	{
		ft_dprintf(stderr, "{red}Error:{eoc} Packet can't be null\n");
		return ;
	}
	ft_printf("Packet ({red}%p{eoc}): ", packet);
	do {
		room = ((t_node*)packet_tmp->data)->next; // From start + 1
		do {
			if (seen[((t_room*)room->data)->id] == 1) {
//				printmatrix(l->flows, l->roomcount);
				r = (t_room*)room->data;
				ft_printf("{red}Invalid. {eoc}", packet);
				ft_printf("Error: duplication of rooms nº%d (%s) on path %p\n",
						r->id, r->name, packet_tmp);
				printpacket(l, packet);
				exit(1);
				return ;
			}
			else
				seen[((t_room*)room->data)->id] = 1;
			room = room->next;
		} while (room != ((t_node*)packet_tmp->data)->prev); // To end - 1
		packet_tmp = packet_tmp->next;
	} while (packet_tmp != packet);
	ft_printf("{green}Valid.{eoc}\n");
	//printpacket(l, paths);
}
//			printpath(l, room->data);

void	printpacket(t_lemin *l, t_node *packet)
{
	t_node *curr;

	curr = packet;
	ft_printf("Packet: ({red}%p{eoc})\n", packet);
	while (true)
	{
		ft_printf("\t{lightmagenta}%p{eoc}: ", curr->data);
		ft_printf("({lightblue}%d{eoc})", ll_len(curr->data));
		printpath(l, curr->data);
		curr = curr->next;
		if (curr == packet)
			break ;
	}
}
