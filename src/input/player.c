/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:58:14 by mkling            #+#    #+#             */
/*   Updated: 2025/03/31 11:23:52 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	orient_cursor(t_pt cursor[3], t_pt player, int angle, int size)
{
	cursor[TOP].x = player.x;
	cursor[TOP].y = player.y - size * 0.1;
	cursor[LEFT].x = player.x - size;
	cursor[LEFT].y = player.y + size;
	cursor[RIGHT].x = player.x + size;
	cursor[RIGHT].y = player.y + size;
	rotate_point(&cursor[TOP], &player, angle);
	rotate_point(&cursor[LEFT], &player, angle);
	rotate_point(&cursor[RIGHT], &player, angle);
}

static void	paint_minimap(t_img *img, t_map *map)
{
	int		column;
	int		row;
	t_pt	pt;

	column = 0;
	while (column < map->height)
	{
		row = 0;
		while (row < map->width)
		{
			pt.x = row * map->scale + map->offset_x;
			pt.y = column * map->scale + map->offset_y;
			if (map->tiles[column][row].type == '1')
				paint_square(img, &pt, map->tile_size, GREY);
			if (map->tiles[column][row].type == 'D')
				paint_square(img, &pt, map->tile_size, ORANGE);
			row++;
		}
		column++;
	}
}

void	update_player_cursor(t_cub *cub)
{
	paint_minimap(&cub->visual, cub->map);
	orient_cursor(cub->player.cursor, cub->player.map_pt, cub->player.angle, cub->map->cursor_size);
	paint_triangle(&cub->visual, cub->player.cursor, WHITE);
}

void	initialize_player(t_cub *cub, float x, float y, int orientation)
{
	cub->player.grid_pt.x = x + 0.5;
	cub->player.grid_pt.y = y + 0.5;
	if (orientation == 'N')
		cub->player.angle = 0.00;
	if (orientation == 'E')
		cub->player.angle = 90.00;
	if (orientation == 'S')
		cub->player.angle = 180.00;
	if (orientation == 'W')
		cub->player.angle = 270.00;
	cub->player.map_pt = scale_point(cub->player.grid_pt, cub->map->scale);
}
