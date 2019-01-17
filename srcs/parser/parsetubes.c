/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetubes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:46:02 by lroux             #+#    #+#             */
/*   Updated: 2019/01/17 11:47:00 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool	maketubes(t_lemin *lemin, char *line)
{
	if (!(lemin->tubes = ft_calloc(lemin->roomcount, sizeof(*lemin->tubes))))
		return (false);
	(void)line;
	return (true);
}
