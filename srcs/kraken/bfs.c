/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/02/06 00:53:48 by glodi            ###   ########.fr       */
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

	//prev = (int)ll_get(path, -2)->data;
	current = (int)ll_get(path, -1)->data;
	if (current == -1)
		return ;
	newpath = 0;
	next = -1;
	while (++next < lemin->roomcount)
	{
		if (lemin->tubes[current][next] == 1
			&& lemin->flows[current][next] != 1 // E.g. == -1 || == 0
			&& !visited[next])
		{
			newpath = ll_dup(path);
			ll_addint(&newpath, next);
			ll_add(q, (void *)newpath);
			printpath(lemin, newpath);
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
	ll_addint(&path, lemin->startid);
	ll_add(&q, path);
	visited[lemin->startid] = true;
	while ((path = ll_pop(&q, 0)))
	{
		ft_printf("->>> (%d)\n", ll_get(path, -1));
		if (*((int*)ll_get(path, -1)->data) == lemin->endid)
		{
			/* TODO: Free queue */
			free(visited);
			return (path);
		}
		updatequeue(lemin, &q, path, visited);
		ft_printf("<<<- (%d)\n", (int)*(ll_get(path, -1)->data));
		/* TODO: Free path */
	}
	return (NULL);
}
