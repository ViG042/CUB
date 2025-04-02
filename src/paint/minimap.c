/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/04/02 13:12:39 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_tile	turn_to_tile(t_cub *cub, int row, int column)
{
	t_tile	tile;

	tile.y = row;
	tile.x = column;
	tile.type = 0;
	tile.state = 0;
	tile.type = cub->map->clean_map[row][column];
	if (tile.type == 'W' || tile.type == 'E'
		|| tile.type == 'N' || tile.type == 'S')
	{
		initialize_player(cub, (float)tile.x, (float)tile.y, tile.type);
		tile.type = '0';
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

void	init_minimap(t_map *map)
{
	int		minimap_max_height;
	int		minimap_max_width;
	float	scale_width;
	float	scale_height;

	minimap_max_height = WIN_HEIGHT * MINIMAP_PROPORTION * 0.7;
	minimap_max_width = WIN_WIDTH * MINIMAP_PROPORTION * 0.7;
	scale_height = (float)minimap_max_height / map->height;
	scale_width = (float)minimap_max_width / map->width;
	map->scale = (int)fmin(scale_height, scale_width);
	map->tile_size = (int)(map->scale);
	map->offset_x = (int)(map->scale);
	map->offset_y = (int)(map->scale);
	map->cursor_size = map->tile_size * 0.8;
}
