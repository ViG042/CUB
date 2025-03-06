/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:35:23 by mkling            #+#    #+#             */
/*   Updated: 2025/03/06 22:41:18 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	verify_char(t_cub *cub, int y, int x)
{
	if (cub->map->array[y][x] == '0' || cub->map->array[y][x] == '1'
			|| cub->map->array[y][x] == 'C' || cub->map->array[y][x] == 'E'
			|| cub->map->array[y][x] == 'P' || cub->map->array[y][x] == 'B')
	{
		;
	}
	else
		exit_if(1, UNKNOWN, cub);
}

static void	verify_line(t_cub *cub, int y)
{
	int	x;

	x = 0;
	while (cub->map->array[y][x])
	{
		verify_char(cub, y, x);
		x++;
	}
}

static void	set_width_and_height(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (cub->map->array[0][x])
		x++;
	cub->map->width = x;
	while (cub->map->array[y])
	{
		verify_line(cub, y);
		y++;
	}
	soft_exit_if(x > 38 || y > 20, TOO_BIG);
	cub->map->height = y;
}

static int	check_walls(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while (cub->map->array[0][x] == '1')
		x++;
	if (x != cub->map->width)
		return (0);
	x = 0;
	while (cub->map->array[cub->map->height - 1][x] == '1')
		x++;
	if (x != cub->map->width)
		return (0);
	y = 0;
	while (cub->map->array[y] && cub->map->array[y][0] == '1')
		y++;
	if (y != cub->map->height)
		return (0);
	y = 0;
	while (cub->map->array[y] && cub->map->array[y][cub->map->width - 1] == '1')
		y++;
	if (y != cub->map->height)
		return (0);
	return (1);
}


void	check_map_syntax(t_cub *cub)
{
	set_width_and_height(cub);
	exit_if(!check_walls(cub), NOT_RECT, cub);
}
