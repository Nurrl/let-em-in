/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:02:08 by glodi             #+#    #+#             */
/*   Updated: 2019/01/31 19:15:12 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	lastroom(int *path, int size)
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

static void	updatequeue(t_lemin *lemin, t_paths *q,
		int *path, t_bool *visited)
{
	int	adjacent;
	int roomid;
	int	*newpath;

	roomid = lastroom(path, lemin->roomcount);
	adjacent = -1;
	while (++adjacent < lemin->roomcount)
	{
		if (lemin->tubes[roomid][adjacent] == 1
			&& lemin->flows[roomid][adjacent] != 1
			&& visited[adjacent] == false)
		{
			newpath = pathdup(lemin->roomcount + 1, path, adjacent);
			q_append(q, newpath);
			visited[adjacent] = true;
		}
	}
}

int			*initpath(int count, size_t size)
{
	int *path;

	if (!(path = malloc(count * size)))
		return (NULL);
	while (--count > -1)
		path[count] = -1;
	return (path);
}

/*
** The value returned will have lemin->roomcount size
** and all value unitialized will be set to -1
*/

int			*bfs(t_lemin *lemin)
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
		if (lastroom(path, lemin->roomcount) == lemin->endid)
		{
			ft_memdel((void **)&visited);
			q_destroy(&q);
			return (path);
		}
		updatequeue(lemin, &q, path, visited);
		ft_memdel((void **)&path);
	}
	ft_memdel((void **)&visited);
	return (NULL);
}
