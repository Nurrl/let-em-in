/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortestpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/01/22 17:28:07 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	*shortestpath(t_lemin lemin, int start, int end)
{
	t_nodes	*queue;
	int		*path;
	int		*visited;
	int		adjacent;

	queue = nd_init(nd_init(start));
	visited = ft_calloc(lemin->roomcount, sizeof(int));
	adjacent = -1;
	while (queue->head)
	{
		path = nd_pophead(queue);
		node = nd_gettail(queue);
		if (node->val == end)
			return (path);
		while (++adjacent < lemin->roomcount)
		{
			if (matrix[node][adjacent] == 1 && visited[adjacent] == 0)
			{
				newpath = ll_dup(path);
				nd_pushtail(newpath, adjacent);
				nd_pushtail(queue, newpath);
				visited[adjacent] = 1;
			}
		}
	}
	return (NULL);
}
