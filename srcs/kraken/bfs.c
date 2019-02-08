/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/02/08 14:35:34 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	updatequeue(t_lemin *lemin, t_node **q,
		t_node *path, t_bool *visited)
{
	//int prev;
	int		next;
	int		current;
	t_node	*newpath;

	//prev = ((t_room*)ll_get(path, -2)->data)->id;
	current = ((t_room*)ll_get(path, -1)->data)->id;
	if (current == -1)
		return ;
	newpath = 0;
	next = -1;
	while (++next < lemin->roomcount)
	{
		if (lemin->tubes[current][next] == 1
			&& lemin->flows[current][next] != 1
			&& !visited[next])
		{
			newpath = ll_dup(path);
			ll_add(&newpath, &lemin->rooms[next]);
			ll_add(q, newpath);
			visited[next] = true;
		}
	}
}

/*
** The value returned will have lemin->roomcount size
** and all value unitialized will be set to -1
*/
t_node		*bfs(t_lemin *lemin)
{
	t_node	*q;
	t_node	*path;
	t_bool	*visited;

	if (!(visited = ft_calloc(lemin->roomcount, sizeof(*visited))))
		return (NULL);
	q = 0;
	path = 0;
	ll_add(&path, &lemin->rooms[lemin->startid]);
	ll_add(&q, path);
	visited[lemin->startid] = true;
	while ((path = ll_pop(&q, 0)))
	{
		if (((t_room*)ll_get(path, -1)->data)->id == lemin->endid)
		{
			/* TODO: Free queue */
			free(visited);
			return (path);
		}
		updatequeue(lemin, &q, path, visited);
		/* TODO: Free path */
	}
	return (NULL);
}
