/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 23:51:08 by glodi             #+#    #+#             */
/*   Updated: 2019/02/14 04:36:53 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** This will inject one ant for each path in packet by adding ant to q
*/

static void	injectall(t_lemin *lemin, t_node *path, t_node **q, int *antid)
{
	t_ant		*ant;

	while (*antid < lemin->antcount)
	{
		if (!(ant = ft_calloc(1, sizeof(*ant))))
			return ;
		ant->id = (*antid)++;
		ant->pos = ((t_node*)path->data)->next;
		ll_add(q, ant);
	}
}

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
		if (antid < lemin->antcount && lemin->turns - (int)ll_len(tmp->data)
				> turn - 2)
		{
			if (!(ant = ft_calloc(1, sizeof(*ant))))
				return ;
			ant->id = antid++;
			ant->pos = ((t_node*)tmp->data)->next;
			ll_add(q, ant);
			if (((t_room*)ant->pos->data)->id == lemin->endid)
				injectall(lemin, tmp, q, &antid);
		}
		tmp = tmp->next;
		if (tmp == packet)
			break ;
	}
}

void		printants(t_lemin *lemin, t_node *packet)
{
	static int		turn;
	static t_node	*q;
	static t_node	*newq;
	t_ant			*ant;

	inject(lemin, packet, &q, turn);
	ft_printf("\n");
	while ((ant = ll_pop(&q, 0)))
	{
		ft_printf("L%d-%s ", ant->id + 1, ((t_room*)ant->pos->data)->name);
		if (((t_room*)ant->pos->data)->id != lemin->endid)
		{
			ant->pos = ant->pos->next;
			ll_add(&newq, ant);
		}
		else
			free(ant);
		if (!q && (q = newq))
		{
			newq = NULL;
			inject(lemin, packet, &q, ++turn);
			ft_printf("\n");
		}
	}
	ft_printf("\n");
}
