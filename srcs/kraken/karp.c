/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:23:33 by glodi             #+#    #+#             */
/*   Updated: 2019/02/02 17:28:59 by glodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		*p_append(int *path, int toadd)
{
	int	i;

	i = -1;
	while (path[++i] != -1)
		;
	path[i] = toadd;
	path[i + 1] = -1;
	return (path);
}

static int		*setpath(t_lemin *lemin, int **f, int pos, int *path)
{
	int	i;

	if (pos == lemin->endid)
		return (path);
	i = -1;
	while (++i < lemin->roomcount && f[pos][i] != 1)
		;
	return (setpath(lemin, f, i, p_append(path, i)));
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
			path = setpath(lemin, f, i, path);
			q_append(batchpaths, path);
		}
	}
	return (batchpaths);
}

void		printmatrix(int **f, size_t size)
{
	int i;
	int y;

	i = -1;
	while (++i < size && (y = -1) == -1)
	{
		while (++y < size)
		{
			if (f[i][y] == -1)
				ft_printf(" -1", f[i][y]);
			else if (f[i][y] == 1)
				ft_printf("  1", f[i][y]);
			else
				ft_printf("  0", f[i][y]);
		}
		ft_printf("\n");
	}
}

static t_bool	applyflow(int **f, int *path)
{
	int i;

	if (!path)
		return (false);
	i = 0;
	while (path[++i] != -1)
	{
		f[path[i]][path[i - 1]] -= 1;
		f[path[i - 1]][path[i]] += 1;
	}
	free(path);
	return (true);
}

static void	checkduplicate(t_lemin *l, t_paths *paths)
{
	int *seen = calloc(l->roomcount, sizeof(*seen));
	t_path *node;

	node = paths->head;
	while (node)
	{
		for (int i = 1; node->path[i + 1] != -1; i++) // From start + 1 to end - 1
		{
			if (seen[node->path[i]] == 1)
			{
//				printmatrix(l->flows, l->roomcount);
				ft_dprintf(stderr, "{red}Invalid packet %p:{eoc}\
 duplication of rooms nº%d (%s) on path %p\n", paths, i, l->rooms[i].name, node);
//				printpacket(l, paths);
				return ;
			}
			else
				seen[node->path[i]] = 1;
		}
		node = node->next;
	}
	ft_dprintf(stderr, "{green}Valid packet %p{eoc}\n", paths);
//		printpacket(l, paths);
}
t_paths			*karp(t_lemin *l,
		t_bool (*evalpacket)(t_lemin *lemin, t_paths *packet, t_paths *best))
{
	int		i;
	t_paths	*best;
	int		**bestf;
	t_paths	*current;

	best = NULL;
	if (!(l->flows = (int **)ft_mk2array(
			l->roomcount, l->roomcount, sizeof(**l->flows))))
		return (NULL);
	while (applyflow(l->flows, bfs(l)))
	{
		current = extractpaths(l, l->flows);
		checkduplicate(l, current);
		if (evalpacket(l, current, best))
			best = current;
		//printmatrix(l->flows, l->roomcount);
	}
	i = -1;
	while (++i < l->roomcount)
		free(l->flows[i]);
	free(l->flows);
	l->flows = NULL;
	return (best);
}
