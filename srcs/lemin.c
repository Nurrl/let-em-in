/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:35:48 by lroux             #+#    #+#             */
/*   Updated: 2019/01/28 15:33:18 by lroux            ###   ########.fr       */
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
	lines = lemin->lines;
	while (lines)
	{
		if (lines->line)
			ft_printf("%s\n", lines->line);
		lines = lines->next;
	}
	collectlines(lemin->lines);
}

void	printpacket(t_lemin *l, t_paths *paths)
{
	t_path *node;

	node = paths->head;
	ft_printf("Packet:\n");
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
		ft_printf("\t%p: ", node->path);

		int i = 0;
		for (i = 0; node->path[i] != -1 && i < 18; i++)
		{
			if (node->path[i] == l->startid)
				ft_printf("{green}");
			if (node->path[i] == l->endid)
				ft_printf("{red}");
			ft_printf("%s{eoc}", l->rooms[node->path[i]].name);
			if (node->path[i + 1] != -1)
				ft_printf(" > ");
		}
		if (i < len)
			ft_printf("...(+%d/%d)", i, len);
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
	factor = (totlen + l->antcount) / pathcount;
	return (factor);
}

static t_bool	evalpacket(t_lemin *l, t_paths *packet, t_paths *best)
{
	float	pflow;
	float	bflow;

	printpacket(l, packet);
	if (!best)
		return (true);
	pflow = flowfactor(l, packet);
	bflow = flowfactor(l, best);
	return ((pflow < bflow) ? true : false);
}

int				main(void)
{
	static t_lemin	lemin;
	static t_paths	*packet;

	if (!parser(&lemin) && collectlines(lemin.lines))
		return (exiterr());
	if (!(packet = karp(&lemin, &evalpacket)) && collectlines(lemin.lines))
		return (exiterr());
	/* printlines(&lemin); */
	ft_printf("The {lightmagenta}lovely{eoc} packet:\n");
	printpacket(&lemin, packet);
	/* Clear the structure (free) */
	return (0);
}
