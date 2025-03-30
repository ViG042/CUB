/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/03/30 21:24:57 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_tile	turn_to_tile(t_cub *cub, int row, int column)
{
	t_tile	tile;

	tile.y = row;
	tile.x = column;
	tile.type = 0;
	if (cub->map->clean_map[row][column])
		tile.type = cub->map->clean_map[row][column];
	if (tile.type == 'W' || tile.type == 'E'
		|| tile.type == 'N' || tile.type == 'S')
	{
		initialize_player(cub, (float)tile.x, (float)tile.y, tile.type);
		tile.type = '0';
		// cub->map->clean_map[row][column] = '0';
	}
	return (tile);
}

void	transform_map_into_tiles(t_cub *cub)
{
	int		row;
	int		column;

	row = 0;
	cub->map->tiles = ft_calloc((cub->map->height) + 1, sizeof(t_tile *));
	exit_if(!cub->map->tiles, MALLOC_FAIL, cub);
	while (cub->map->clean_map[row])
	{
		cub->map->tiles[row] = ft_calloc((cub->map->width) + 1, sizeof(t_tile));
		exit_if(!cub->map->tiles[row], MALLOC_FAIL, cub);
		column = 0;
		while (cub->map->clean_map[row][column] != '\0')
		{
			cub->map->tiles[row][column] = turn_to_tile(cub, row, column);
			column++;
			cub->map->pt_count++;
		}
		row++;
	}
}

static void	orient_player_cursor(t_cub *cub)
{
	cub->player.cursor[TOP].x = cub->player.map_pt.x;
	cub->player.cursor[TOP].y
		= cub->player.map_pt.y - cub->player.cursor_size * 0.1;
	cub->player.cursor[LEFT].x
		= cub->player.map_pt.x - cub->player.cursor_size;
	cub->player.cursor[LEFT].y
		= cub->player.map_pt.y + cub->player.cursor_size;
	cub->player.cursor[RIGHT].x
		= cub->player.map_pt.x + cub->player.cursor_size;
	cub->player.cursor[RIGHT].y
		= cub->player.map_pt.y + cub->player.cursor_size;
	rotate_point(cub, &cub->player.cursor[TOP], &cub->player.map_pt,
		cub->player.player_angle);
	rotate_point(cub, &cub->player.cursor[LEFT], &cub->player.map_pt,
		cub->player.player_angle);
	rotate_point(cub, &cub->player.cursor[RIGHT], &cub->player.map_pt,
		cub->player.player_angle);
}

static void	paint_map(t_img *img, t_map *map)
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

void	paint_minimap(t_cub *cub)
{
	paint_map(&cub->visual, cub->map);
	orient_player_cursor(cub);
	paint_triangle(&cub->visual, cub->player.cursor, WHITE);
}
