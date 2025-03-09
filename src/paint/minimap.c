/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 19:05:18 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	orient_player_cursor(t_cub *cub)
{
	cub->player.cursor[TOP].x = cub->player.map_pt.x;
	cub->player.cursor[TOP].y = cub->player.map_pt.y - CURSOR_SIZE * 0.1;
	cub->player.cursor[LEFT].x = cub->player.map_pt.x - CURSOR_SIZE;
	cub->player.cursor[LEFT].y = cub->player.map_pt.y + CURSOR_SIZE;
	cub->player.cursor[RIGHT].x = cub->player.map_pt.x + CURSOR_SIZE;
	cub->player.cursor[RIGHT].y = cub->player.map_pt.y + CURSOR_SIZE;
	rotate_point(cub, &cub->player.cursor[TOP], &cub->player.map_pt,
		cub->player.player_angle);
	rotate_point(cub, &cub->player.cursor[LEFT], &cub->player.map_pt,
		cub->player.player_angle);
	rotate_point(cub, &cub->player.cursor[RIGHT], &cub->player.map_pt,
		cub->player.player_angle);
}

static void	paint_map(t_cub *cub)
{
	int		index;
	t_pt	pt;

	index = 0;
	while (index < cub->map->pt_count)
	{
		pt = cub->minimap->pts_array[index];
		if (pt.type == '1')
			paint_square(&cub->img, &pt, MINIMAP_TILE_SIZE, GREY);
		if (pt.type == '0' || pt.type == 'N' || pt.type == 'E'
			|| pt.type == 'S' || pt.type == 'W')
			paint_square(&cub->img, &pt, MINIMAP_TILE_SIZE, DARK_GREY);
		if (pt.type == 'D')
			paint_square(&cub->img, &pt, MINIMAP_TILE_SIZE, ORANGE);
		index++;
	}
}

void	paint_minimap(t_cub *cub)
{
	paint_map(cub);
	orient_player_cursor(cub);
	paint_triangle(&cub->img, cub->player.cursor, WHITE);
}
