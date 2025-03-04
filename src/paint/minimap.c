/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/03/04 19:16:34 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	paint_player(t_cub *cub)
{
	cub->player.rgb = WHITE;
	paint_triangle(cub, &cub->player, WHITE);
}

void	paint_walls(t_cub *cub)
{
	int		row;
	int		column;
	t_pt	wall;

	column = 0;
	while (cub->map->array[column])
	{
		row = 0;
		while (cub->map->array[column][row])
		{
			if (cub->map->array[column][row] == '1')
			{
				wall.x = row * UNIT * 2 + 20;
				wall.y = column * UNIT * 2 + 20;
				paint_square(cub, &wall, GREY);
			}
			else
			{
				wall.x = row * UNIT * 2 + 20;
				wall.y = column * UNIT * 2 + 20;
				paint_square(cub, &wall, BLACK);
			}
			row++;
		}
		column++;
	}
}

void	print_grid(t_cub *cub)
{
	int		index;
	t_pt	pt;

	index = 0;
	while (index < cub->map->size)
	{
		pt = cub->map->pts_array[index];
		put_point(cub, pt);
		index++;
	}
}

void	paint_minimap(t_cub *cub)
{
	paint_walls(cub);
	paint_player(cub);
}
