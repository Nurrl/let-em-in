/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:35:48 by lroux             #+#    #+#             */
/*   Updated: 2019/02/12 03:27:08 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	exiterr(void)
{
	ft_printf("ERROR\n");
	return (1);
}

static float	flowfactor(t_lemin *l, t_node *packet)
{
	float	factor;
	int		totcount;
	int		pathcount;
	t_node	*curr;

	totcount = 0;
	pathcount = 0;
	curr = packet;
	while (true)
	{
		totcount += ll_len(curr->data);
		curr = curr->next;
		pathcount++;
		if (curr == packet)
			break ;
	}
//	factor = ((totcount - (pathcount * 2)) + l->antcount) / pathcount; // Old forula
	factor = ((totcount + l->antcount) / pathcount - 1); // Xavier formula
	return (factor);
}

static t_bool	evalpacket(t_lemin *l, t_node *packet, t_node *best)
{
	float	pflow;
	t_bool	isbest;

	pflow = flowfactor(l, packet);
	if (!best)
		isbest = true;
	else
		isbest = ((pflow < l->kr.bestflow) ? true : false);
	if (isbest)
		l->turns = (int)pflow;
	if (isbest)
		l->kr.bestflow = pflow;
	return (isbest);
}

static void	printlines(t_lemin *lemin)
{
	char *l;

	while (keepgnl(stdin, &l, lemin) > 0)
		;
	while ((l = ll_pop(&lemin->lines, 0)))
		ft_printf("%s\n", l);
}

int				main(void)
{
	static t_lemin	lemin;
	static t_node	*packet;

	if (!parser(&lemin) && ll_del(&lemin.lines))
		return (exiterr());
	if (!(packet = karp(&lemin, &evalpacket)) && ll_del(&lemin.lines))
		return (exiterr());
	printlines(&lemin);

	// ft_printf("The {lightmagenta}lovely{eoc} packet: Turn count '%d' for {yellow}%d{eoc} ants.\n", lemin.turns, lemin.antcount);
	ft_printf("Turn count '%d' for {yellow}%d{eoc} ants.\n", lemin.turns, lemin.antcount);
	printpacket(&lemin, packet);
	printants(&lemin, packet);

	/* TODO: Free superstructure */
	return (0);
}
