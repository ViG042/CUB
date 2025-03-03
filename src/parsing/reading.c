/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:34:13 by mkling            #+#    #+#             */
/*   Updated: 2025/03/03 15:28:11 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	verify_char(t_cub *cub, int y, int x)
{
	if (cub->map->array[y][x] == '0' || cub->map->array[y][x] == '1'
			|| cub->map->array[y][x] == 'C' || cub->map->array[y][x] == 'E'
			|| cub->map->array[y][x] == 'P' || cub->map->array[y][x] == 'B')
	{
		if (cub->map->array[y][x] == 'P')
		{
			cub->i_player++;
			cub->new_y = y;
			cub->new_x = x;
			cub->new_c = '0';
			cub->p_x = x;
			cub->p_y = y;
		}
		if (cub->map->array[y][x] == 'E')
			cub->i_exit++;
		if (cub->map->array[y][x] == 'C')
		{
			cub->i_coin++;
			cub->i_coin_copy++;
			cub->i_life++;
		}
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
	exit_if(x != cub->map->width, NOT_RECT, cub);
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
	cub->map->width = y;
	cub->map->total = x * y;
}

void	read_map_into_buffer(t_cub *cub)
{
	int	map_size;

	cub->fd = open(cub->map->name, O_RDONLY);
	soft_exit_if(cub->fd < 0, OPEN_FAIL);
	map_size = read(cub->fd, cub->temp_map, 1020);
	soft_exit_if(map_size < 0, READ_FAIL);
	cub->temp_map[map_size] = '\0';
	soft_exit_if((read(cub->fd, cub->temp_map, 1) != 0), TOO_BIG);
	set_width_and_height(cub);
}


