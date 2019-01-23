/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/01/23 18:59:42 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// static void	printpath(int *path)
// {
// 	for (int i = 0; path[i] != -1; i++)
// 	{
// 		ft_printf("%d>", path[i]);
// 	}
// 	ft_printf("\n");
// }

static int *initpath(int count, size_t size)
{
	int *path;

	if (!(path = malloc(count * size)))
		return (NULL);
	while (--count > -1)
		path[count] = -1;
	return (path);
}

static int	lastnode(int *path, int size)
{
	int i;

	if (!path)
		return (-1);
	i = -1;
	while (path[++i] != -1 && i < size)
		;
	if (i > 1)
		return (path[i - 1]);
	return (0);
}

static int	*pathdup(int size, int *path, int toadd)
{
	int *newpath;
	int	i;

	if (!(newpath = ft_calloc(size, sizeof(*newpath))))
		return (NULL);
	ft_memcpy(newpath, path, size * sizeof(*newpath));
	i = -1;
	while (newpath[++i] != -1 && i < size)
		;
	newpath[i] = toadd;
	return (newpath);
}

static void updatequeue(t_lemin *lemin, t_paths *q, int *path, t_bool *visited)
{
	int	adjacent;
	int node;
	int	*newpath;

	node = lastnode(path, lemin->roomcount);
	adjacent = -1;

	while (++adjacent <= lemin->roomcount)
	{
		if (lemin->tubes[node][adjacent] == 1 && visited[adjacent] == false)
		{
			newpath = pathdup(lemin->roomcount + 1, path, adjacent);
			visited[adjacent] = true;
			q_append(q, newpath);
		}
	}
}

/*
** The value returned will have lemin->roomcount size
** and all value unitialized will be set to -1
*/
int		*bfs(t_lemin *lemin)
{
	t_paths	q;
	int		*path;
	t_bool	*visited;

	q = (t_paths){0, 0};
	if (!(visited = ft_calloc(lemin->roomcount, sizeof(*visited))))
		return (NULL);
	if (!(path = initpath(lemin->roomcount + 1, sizeof(*path))))
		return (NULL);
	path[0] = lemin->startid;
	q_append(&q, path);
	while ((path = q_pophead(&q)))
	{
		if (lastnode(path, lemin->roomcount) == lemin->endid)
			return (path); // free q before svp
		updatequeue(lemin, &q, path, visited);
	}
	return (NULL);
}