/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 23:51:08 by glodi             #+#    #+#             */
/*   Updated: 2019/02/14 02:43:12 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** This will inject one ant for each path in packet by adding ant to q
*/

static void	inject(t_lemin *lemin, t_node *packet, t_node **q, int turn)
{
	static int	antid = 0;
	t_node		*tmp;
	t_ant		*ant;

	if (antid == lemin->antcount)
		return ;
	tmp = packet;
	while (true)
	{
		if (antid < lemin->antcount
				&& lemin->turns - (int)ll_len(tmp->data) > turn - 2)
		{
			if (!(ant = ft_calloc(1, sizeof(*ant))))
				return ;
			ant->id = antid++;
			ant->pos = ((t_node*)tmp->data)->next;
			ll_add(q, ant);
		}
		tmp = tmp->next;
		if (tmp == packet)
			break ;
	}
}

static void	ingest(t_lemin *lemin, t_node *packet, t_node **q, int turn)
{
	static int	turnsave = -1;
	static int	antid;
	t_node		*path;
	t_ant			*ant;

	/* Nouveau tour */
	if (turn != turnsave && (turn = turnsave))
		ft_printf("\n");
	else
		return ;
	path = packet;
	while (true)
	{
		if (antid < lemin->antcount
				&& turn + (int)ll_len(path->data) < lemin->turns)
		{
			if (!(ant = ft_calloc(1, sizeof(*ant))))
				return ;
			ant->id = antid++;
			ant->pos = ((t_node*)path->data)->next;
			ll_add(q, ant);
		}
		path = path->next;
		if (path == packet)
			break ;
	}
}

void		printants(t_lemin *lemin, t_node *packet)
{
	static int		turn;
	static t_node	*q;
	static t_node	*nextq;
	t_ant			*ant;

	ft_printf("\n");
	ingest(lemin, packet, &q, turn);
	while ((ant = ll_pop(&q, 0)))
	{
		ft_printf("L%d-%s ", ant->id + 1, ((t_room*)ant->pos->data)->name);
		if (((t_room*)ant->pos->data)->id != lemin->endid)
			ll_add(&nextq, ant);
		else
			free(ant);
		ant->pos = ant->pos->next;
		if (!q && (q = nextq))
			turn++;
		ingest(lemin, packet, &q, turn);
	}
}
