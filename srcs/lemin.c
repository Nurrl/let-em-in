/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:35:48 by lroux             #+#    #+#             */
/*   Updated: 2019/02/01 18:11:30 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	exiterr(void)
{
	ft_printf("ERROR\n");
	return (1);
}

void	printlines(t_lemin *lemin)
{
	t_line	*lines;
	char	*l;

	while (keepgnl(stdin, &l, lemin) > 0)
		;
	lines = lemin->kr.lines;
	while (lines)
	{
		if (lines->line)
			ft_printf("%s\n", lines->line);
		lines = lines->next;
	}
	collectlines(lemin->kr.lines);
}

void	printpacket(t_lemin *l, t_paths *paths)
{
	t_path *node;

	node = paths->head;
	ft_printf("Packet: ({red}%p{eoc})\n", node);
	while (node)
	{
		if (!node->path)
		{
			ft_printf("\t{red}{shrug}{eoc}\n");
			break;
		}
		int len = 0;
		for (len = 0; node->path[len] != -1; len++)
			len++;
		len--;
		ft_printf("\t{lightmagenta}%p{eoc}: ", node->path);

		int i = 0;
		for (i = 0; node->path[i] != -1; i++)
		{
			//if (node->path[i] == l->startid)
			//	ft_printf("{green}");
			//if (node->path[i] == l->endid)
			//	ft_printf("{red}");
			ft_printf("%s", l->rooms[node->path[i]].name);
			if (node->path[i + 1] != -1)
				ft_printf(" > ");
		}
		ft_printf("({blue}%d{eoc})", i, len);
		ft_printf("\n");
		node = node->next;
	}
}

/*
** Flow factor of packet:
** (pathtotlen + antcount) / pathcount
*/
static float	flowfactor(t_lemin *l, t_paths *p)
{
	float	factor;
	int		totlen;
	int		pathcount;
	t_path	*cur;
	int		i;

	totlen = 0;
	pathcount = 0;
	cur = p->head;
	while (cur)
	{
		i = -1;
		while (cur->path[++i] != -1)
			totlen++;
		cur = cur->next;
		pathcount++;
	}
	factor = ((totlen - (pathcount * 2)) + l->antcount) / pathcount;
	return (factor);
}

static t_bool	evalpacket(t_lemin *l, t_paths *packet, t_paths *best)
{
	float	pflow;
	t_bool	isbest;

	//printpacket(l, packet);
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

int				main(void)
{
	static t_lemin	lemin;
	static t_paths	*packet;

	if (!parser(&lemin) && collectlines(lemin.kr.lines))
		return (exiterr());
//	printmatrix(lemin.tubes, lemin.roomcount);
	ft_dprintf(stderr, "start = %s, end = %s\n", lemin.rooms[lemin.startid].name, lemin.rooms[lemin.endid].name);
	if (!(packet = karp(&lemin, &evalpacket)) && collectlines(lemin.kr.lines))
		return (exiterr());
//	printlines(&lemin);
	ft_printf("The {lightmagenta}lovely{eoc} packet: Turn count '%d' for {yellow}%d{eoc} ants.\n", lemin.turns, lemin.antcount);
	printpacket(&lemin, packet);
	/* Clear the structure (free) */
	return (0);
}
