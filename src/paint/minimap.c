/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 17:03:42 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	orient_player_cursor(t_cub *cub)
{
	cub->player.cursor[TOP].x = cub->player.player_pt.x;
	cub->player.cursor[TOP].y = cub->player.player_pt.y - CURSOR_SIZE * 0.1;
	cub->player.cursor[LEFT].x = cub->player.player_pt.x - CURSOR_SIZE;
	cub->player.cursor[LEFT].y = cub->player.player_pt.y + CURSOR_SIZE;
	cub->player.cursor[RIGHT].x = cub->player.player_pt.x + CURSOR_SIZE;
	cub->player.cursor[RIGHT].y = cub->player.player_pt.y + CURSOR_SIZE;
	rotate_point(cub, &cub->player.cursor[TOP], &cub->player.player_pt,
		cub->player.player_angle);
	rotate_point(cub, &cub->player.cursor[LEFT], &cub->player.player_pt,
		cub->player.player_angle);
	rotate_point(cub, &cub->player.cursor[RIGHT], &cub->player.player_pt,
		cub->player.player_angle);
}

static void	paint_map(t_cub *cub)
{
	int		index;
	t_pt	pt;

	index = 0;
	while (index < cub->map->size)
	{
		pt = cub->map->pts_array[index];
		if (pt.type == '1')
			paint_square(&cub->img, &pt, MINIMAP_TILE_SIZE, GREY);
		if (pt.type == '0' || pt.type == 'N')
			paint_square(&cub->img, &pt, MINIMAP_TILE_SIZE, DARK_GREY);
		index++;
	}
}

void	paint_minimap(t_cub *cub)
{
	paint_map(cub);
	orient_player_cursor(cub);
	paint_triangle(&cub->img, cub->player.cursor, WHITE);
}
