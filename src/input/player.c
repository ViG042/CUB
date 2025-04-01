/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:58:14 by mkling            #+#    #+#             */
/*   Updated: 2025/04/01 20:39:30 by alex             ###   ########.fr       */
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
	cub->player.map_pt = scale_point(cub->player.grid_pt, cub->map->scale);
	orient_cursor(cub->player.cursor, cub->player.map_pt, cub->player.deg_angle, cub->map->cursor_size);
	paint_triangle(&cub->visual, cub->player.cursor, WHITE);
}

void	initialize_player(t_play *player, float x, float y, int orientation)
{
	player->grid_pt.x = x + 0.5;
	player->grid_pt.y = y + 0.5;
	if (orientation == 'N')
		player->deg_angle = 0.00;
	if (orientation == 'E')
		player->deg_angle = 90.00;
	if (orientation == 'S')
		player->deg_angle = 180.00;
	if (orientation == 'W')
		player->deg_angle = 270.00;
	player->rad_angle = player->deg_angle * RADIAN;
	player->dir.x = cos(player->rad_angle);
	player->dir.y = sin(player->rad_angle);
	player->plane.x = -player->dir.y * tan(FIELD_OF_VIEW / 2 * RADIAN);
	player->plane.y = player->dir.x * tan(FIELD_OF_VIEW / 2 * RADIAN);
	printf("starting dir is %f, %f with plane %f %f\n", player->dir.x, player->dir.y, player->plane.x, player->plane.y);
}
