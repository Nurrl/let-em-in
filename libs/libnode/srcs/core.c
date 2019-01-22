/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <git@heofon.co>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:25:34 by lroux             #+#    #+#             */
/*   Updated: 2019/01/22 17:53:38 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnode.h"

t_nodes	nd_init(void *data)
{
	t_nodes list;

	list.size = 0;
	list.head = NULL;
	list.tail = NULL;
	if (data)
		nd_pushhead(&list, data);
	return (list);
}

void	nd_destroy(t_nodes *list)
{
	while (nd_pophead(list))
		continue ;
}
