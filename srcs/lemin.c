/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:35:48 by lroux             #+#    #+#             */
/*   Updated: 2019/02/14 05:32:13 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		exiterr(void)
{
	ft_printf("ERROR\n");
	return (1);
}

static float	flowfactor(t_lemin *l, t_node *packet)
{
	float	factor;
	float	totcount;
	float	pathcount;
	t_node	*curr;

	totcount = 0;
	pathcount = 0;
	curr = packet;
	while (true)
	{
		totcount += ll_len(curr->data) - 1;
		curr = curr->next;
		pathcount++;
		if (curr == packet)
			break ;
	}
	factor = ((totcount + l->antcount) / pathcount) - 1;
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
		l->turns = (int)(pflow + 0.999999f);
	if (isbest)
		l->kr.bestflow = pflow;
	return (isbest);
}

void			printlines(t_lemin *lemin, t_bool print)
{
	char *l;

	while (keepgnl(stdin, &l, lemin) > 0)
		;
	while ((l = ll_pop(&lemin->lines, 0)))
	{
		if (print)
			ft_printf("%s\n", l);
		free(l);
	}
}

int				main(void)
{
	static t_lemin	lemin;
	static t_node	*packet;

	if (!parser(&lemin) && cleanlemin(&lemin))
		return (exiterr());
	if (!(packet = karp(&lemin, &evalpacket)) && cleanlemin(&lemin))
		return (exiterr());
	printlines(&lemin, true);
	printants(&lemin, packet);
	cleanpacket(&packet);
	cleanlemin(&lemin);
	return (0);
}
