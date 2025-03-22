/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/03/22 11:54:39 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	orient_player_cursor(t_cub *cub)
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

static void	paint_map(t_cub *cub)
{
	int		column;
	int		row;
	t_pt	pt;

	column = 0;
	while (column < cub->map->height)
	{
		row = 0;
		while (row < (int)ft_strlen(cub->map->clean_map[column]))
		{
			pt.x = row * cub->map->scale + cub->map->offset_x;
			pt.y = column * cub->map->scale + cub->map->offset_y;
			if (cub->map->clean_map[column][row])
				pt.type = cub->map->clean_map[column][row];
			if (pt.type == '1')
				paint_square(&cub->visual, &pt, cub->map->tile_size, GREY);
			// if (pt.type == '0')
			// 	;
			if (pt.type == 'D')
				paint_square(&cub->visual, &pt, cub->map->tile_size, ORANGE);
			row++;
		}
		column++;
	}
}

void	paint_minimap(t_cub *cub)
{
	paint_map(cub);
	orient_player_cursor(cub);
	paint_triangle(&cub->visual, cub->player.cursor, WHITE);
}
