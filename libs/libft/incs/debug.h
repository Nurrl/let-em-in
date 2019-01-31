/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroux <lroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:48:16 by lroux             #+#    #+#             */
/*   Updated: 2019/01/31 15:00:38 by lroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <time.h>

# define C_RED "\e[31m"
# define C_GRN "\e[32m"
# define C_YEL "\e[33m"
# define C_RES "\e[39m"

# define CLOCK_START clock_t start = clock();
# define CLOCK_RESTART start = clock();
# define CLOCK_END dprintf(2, "%.2fms %s\n", ((double) (clock() - start)) / (CLOCKS_PER_SEC / 1000), __FUNCTION__);
# define CLOCK_END_COL(s1, s2) do {\
	if (((double) (clock() - start)) / (CLOCKS_PER_SEC / 1000) < s1)\
		dprintf(2, C_GRN "%4.2fms " C_RES "%s\n", \
		((double) (clock() - start)) / (CLOCKS_PER_SEC / 1000), __FUNCTION__);\
	if (((double) (clock() - start)) / (CLOCKS_PER_SEC / 1000) < s2)\
		dprintf(2, C_YEL "%4.2fms " C_RES "%s\n", \
		((double) (clock() - start)) / (CLOCKS_PER_SEC / 1000), __FUNCTION__);\
	else\
		dprintf(2, C_RED "%4.2fms " C_RES "%s\n", \
		((double) (clock() - start)) / (CLOCKS_PER_SEC / 1000), __FUNCTION__);\
	} while (0);

#endif
