/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortestpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/01/22 18:05:05 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	*shortestpath(t_lemin *lemin)
{
	t_nodes	queue;
	t_nodes	path;
	t_nodes	node;
	int		*visited;
	int		adjacent;

	path = nd_init(lemin->rooms.start);
	queue = nd_init(&path);
	if (!(visited = ft_calloc(lemin->roomcount, sizeof(*visited))))
		return (NULL);
	adjacent = -1;
	while (queue.head)
	{
		path = *((t_nodes*)nd_pophead(&queue));
		node = *((t_nodes*)nd_gettail(&queue));
		if (node.data == end) // Nope
			return (path); // Nope
		while (++adjacent < lemin->roomcount)
		{
			if (matrix[node][adjacent] == 1 && visited[adjacent] == 0) // Where is matrix ? 
			{
				newpath = nd_dup(&path);
				nd_pushtail(newpath, adjacent);
				nd_pushtail(queue, newpath);
				visited[adjacent] = 1;
			}
		}
	}
	return (NULL);
}
