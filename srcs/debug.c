/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 19:13:35 by glodi             #+#    #+#             */
/*   Updated: 2019/02/06 00:35:58 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
		ft_printf(" %s", l->rooms[(int)curr->data].name);
		if (curr->next != curr->data)
			ft_printf(" >");
		curr = curr->next;
		if (curr == path)
			break ;
	}
	ft_printf("\n");
}
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

	i = -1;
	while (++i < size && (y = -1) == -1)
	{
		while (++y < size)
		{
			if (f[i][y] == -1)
				ft_printf(" -1", f[i][y]);
			else if (f[i][y] == 1)
				ft_printf("  1", f[i][y]);
			else
				ft_printf("  0", f[i][y]);
		}
		ft_printf("\n");
	}
}

//void	checkduplicate(t_lemin *l, t_node *packet)
//{
//	int *seen = calloc(l->roomcount, sizeof(*seen));
//
//	while (node)
//	{
//		for (int i = 1; node->path[i + 1] != -1; i++) // From start + 1 to end - 1
//		{
//			if (seen[node->path[i]] == 1)
//			{
//				//				printmatrix(l->flows, l->roomcount);
//				ft_dprintf(stderr, "{red}Invalid packet %p:{eoc}"\
//				" duplication of rooms nº%d (%s) on path %p at position: %d\n", paths->head, node->path[i], l->rooms[node->path[i]].name, node->path, i);
//				//				printpacket(l, paths);
//				return ;
//			}
//			else
//				seen[node->path[i]] = 1;
//		}
//		node = node->next;
//	}
//	ft_dprintf(stderr, "{green}Valid packet %p{eoc}\n", paths);
//			//printpacket(l, paths);
//}

void	printpacket(t_lemin *l, t_node *packet)
{
	t_node *curr;
	t_node *curr2;

	curr = packet;
	ft_printf("Packet: ({red}%p{eoc})\n", packet);
	while (true)
	{
		ft_printf("\t{lightmagenta}%p{eoc}: ", curr->data);

		curr2 = curr->data;
		while (true)
		{
			//if (node->path[i] == l->startid)
			//	ft_printf("{green}");
			//if (node->path[i] == l->endid)
			//	ft_printf("{red}");
			ft_printf(" %s", l->rooms[(int)curr2->data].name);
			if (curr2->next != curr->data)
				ft_printf(" >");
			curr2 = curr2->next;
			if (curr2 == curr->data)
				break ;
		}
		ft_printf("({blue}%d{eoc})", ll_len(curr));
		ft_printf("\n");

		curr = curr->next;
		if (curr == packet)
			break ;
	}
}
