/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 23:51:08 by glodi             #+#    #+#             */
/*   Updated: 2019/02/12 04:39:13 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

typedef struct	s_ant {
	int		id;
	t_node	*pos; // Node pos in path
}				t_ant;


/*
** This will inject one ant for each path in packet by adding ant to q
*/
static void	inject(t_lemin *lemin, t_node *packet, t_node **q, int actual_turn)
{
	static int	antid;
	t_node		*tmp;
	t_ant		*ant;

	if (antid == 0)
		antid = 1;
	if (antid - 1 == lemin->antcount)
		return;
	ant = NULL;
	tmp = NULL;
	while (tmp != packet) {
		if (!tmp)
			tmp = packet;
		if (antid <= lemin->antcount
				&& (lemin->turns + 1) - (int)ll_len(tmp->data) >= (actual_turn - 1))
		{
			ant = ft_calloc(1, sizeof(*ant));
			ant->id = antid;
			ant->pos = ((t_node*)tmp->data)->next; // Skip start to first valid room
			ll_add(q, ant);
			antid++;
		}
		tmp = tmp->next;
	}
}

void printants(t_lemin *lemin, t_node *packet)
{
	int actual_turn = 1;
	t_node	*q = NULL;
	t_node	*q_bis = NULL;
	t_ant	*ant = NULL;

	inject(lemin, packet, &q, actual_turn);
	ft_printf("{cyan}%02d: {eoc}", actual_turn);
	while ((ant = ll_pop(&q, 0)))
	{
		ft_printf("L%d-%s ",
				ant->id, ((t_room*)ant->pos->data)->name);
		if (((t_room*)ant->pos->data)->id != lemin->endid)
		{
			ant->pos = ant->pos->next;
			ll_add(&q_bis, ant);
		}
		// else
			// ft_printf("{green}%d, {eoc} ", ant->id);
		if (!q && q_bis)
		{
			actual_turn++;
			ft_printf("\n{cyan}%02d: {eoc}", actual_turn);
			q = q_bis;
			q_bis = NULL;
			inject(lemin, packet, &q, actual_turn);
		}
	}
	ft_printf("\n                          {cyan}Total turns: %02d.{eoc}\n", actual_turn);

}
