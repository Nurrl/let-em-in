/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glodi <glodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:23:33 by glodi             #+#    #+#             */
/*   Updated: 2019/01/28 15:35:47 by lroux            ###   ########.fr       */
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

static t_bool	applyflow(int ***f, int *path)
{
	int i;

	if (!path)
		return (false);
	i = 0;
	while (path[++i] != -1)
	{
		(*f)[path[i]][path[i - 1]] -= 1;
		(*f)[path[i - 1]][path[i]] += 1;
	}
	free(path);
	return (true);
}

t_paths			*karp(t_lemin *l,
		t_bool (*evalpacket)(t_lemin *lemin, t_paths *packet, t_paths *best))
{
	int		i;
	int		**f; // Residual flow matrix
	t_paths	*best;
	t_paths	*current;

	best = NULL;
	if (!(f = (int **)ft_mk2array(l->roomcount, l->roomcount, sizeof(**f))))
		return (NULL);
	while (applyflow(&f, bfs(l, f)))
	{
		current = extractpaths(l, f);
		if (evalpacket(l, current, best))
			best = current;
	}
	i = -1;
	while (++i < l->roomcount)
		free(f[i]);
	free(f);
	return (best);
}
