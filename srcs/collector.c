/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 18:00:44 by lroux             #+#    #+#             */
/*   Updated: 2019/01/21 19:13:03 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool	collectlines(t_line *lines)
{
	t_line *cur;

	while (lines)
	{
		cur = lines;
		lines = lines->next;
		free(cur->line);
		free(cur);
	}
	return (true);
}
