/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/03/04 15:29:51 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	paint_player(t_cub *cub)
{
	cub->player.x = 200 + cub->offset_x;
	cub->player.y = 200 + cub->offset_y;
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
	t_pt	offset_pt;

	index = 0;
	while (index < cub->map->size)
	{
		pt = cub->map->pts_array[index];
		put_point(cub, pt);
		offset_pt = apply_zoom_and_offset(&pt, cub);
		// fprintf(stderr, "offset is %f, %f, %f\n", pt.x, pt.y, pt.z);
		// if (index % cub->map->width != 0)
		// {
		// 	paint_line(cub->map->pts_array[index - 1],
		// 		cub->map->pts_array[index], cub);
		// }
		// if (index >= cub->map->width)
		// {
		// 	paint_line(cub->map->pts_array[index - cub->map->width],
		// 		cub->map->pts_array[index], cub);
		// }
		index++;
	}
}

void	paint_minimap(t_cub *cub)
{
	paint_background(&cub->img, BLACK);
	// print_grid(cub);
	paint_walls(cub);
	paint_player(cub);
}
