/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:23:33 by glodi             #+#    #+#             */
/*   Updated: 2019/01/25 19:07:50 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int *p_append(int *path, int toadd)
{
	int	i;

	i = -1;
	while (path[++i] != -1)
		;
	path[i] = toadd;
	path[i + 1] = -1;
	return (path);
}

static int *setpath(t_lemin *lemin, int **f, int pos, int *path)
{
	int	i;

	if (pos == lemin->endid)
		return (path);
	i = -1;
	while (++i < lemin->roomcount)
	{
		if (f[pos][i] == 1)
			return (setpath(lemin, f, i, p_append(path, i)));
	}
	return (path);
}

static t_paths	*extractpaths(t_lemin *lemin, int **f)
{
	int		i;
	int		*path;
	t_paths	*batchpaths;

	if (!(batchpaths = ft_calloc(1, sizeof(*batchpaths))))
		return (NULL);
	i = -1;
	while (++i < lemin->roomcount)
	{
		if (f[lemin->startid][i] == 1)
		{
			if (!(path = initpath(lemin->roomcount, sizeof(*path))))
				return (NULL);
			path[0] = lemin->startid;
			path[1] = i;
			setpath(lemin, f, i, path);
			q_append(batchpaths, path);
		}
	}
	return (batchpaths);
}

static void	printpaths(t_paths *paths)
{
	t_path *node;

	node = paths->head;
	ft_printf("Batch paths:\n");
	while (node)
	{
		if (!node->path)
		{
			ft_printf("\tpath is null\n");
			break;
		}
		int len = 0;
		for (len = 0; node->path[len] != -1; len++)
			len++;
		len--;
		ft_printf("\t%p: ", node->path);

		int i = 0;
		for (i = 0; node->path[i] != -1 && i < 30; i++)
		{
			ft_printf("%4d ", node->path[i]);
		}
		if (i < len)
			ft_printf("...(+%d/%d)", i, len);
		ft_printf("\n");
		node = node->next;
	}
}

t_paths	*karp(t_lemin *l)
{
	int		i;
	int		**f; // Residual flow matrix / TODO: Free that shit
	int		*path;
	t_paths	*batchpaths;

	if (!(f = (int **)ft_mk2array(l->roomcount, l->roomcount, sizeof(**f))))
		return (NULL);
	while ((path = bfs(l, f)))
	{
		i = 0;
		while (path[++i] != -1)
		{
			f[path[i]][path[i - 1]] -= 1;
			f[path[i - 1]][path[i]] += 1;
//			ft_printf("loop, i=%d, path[i]= %d, path[i+1]= %d\n", i, path[i], path[i+1]);
		}
		ft_memdel((void **)&path);
		batchpaths = extractpaths(l, f);
		printpaths(batchpaths);
	}

	return (batchpaths);
}
