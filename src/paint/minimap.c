/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/03/20 14:45:24 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	orient_player_cursor(t_cub *cub)
{
	t_pt	cursor[3];

	cursor[TOP].x = cub->player.grid_pt.x + cub->player.dir.x;
	cursor[TOP].y = cub->player.grid_pt.y + cub->player.dir.y;
	cursor[LEFT].x
		= cub->player.grid_pt.x;
	cursor[LEFT].y
		= cub->player.grid_pt.y;
	cursor[RIGHT].x
		= cub->player.grid_pt.x;
	cursor[RIGHT].y
		= cub->player.grid_pt.y;
	cub->player.cursor[TOP] = project_point(cub, cursor[TOP]);
	cub->player.cursor[LEFT] = project_point(cub, cursor[LEFT]);
	cub->player.cursor[RIGHT] = project_point(cub, cursor[RIGHT]);
	printf("cursor is top %f %f left %f %f right %f %f\n",
		cub->player.cursor[TOP].x, cub->player.cursor[TOP].y,
		cub->player.cursor[LEFT].x, cub->player.cursor[LEFT].y,
		cub->player.cursor[RIGHT].x, cub->player.cursor[RIGHT].y);
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
				paint_square(&cub->img, &pt, cub->map->tile_size, GREY);
			if (pt.type == '0' || pt.type == 'N' || pt.type == 'E'
				|| pt.type == 'S' || pt.type == 'W')
				paint_square(&cub->img, &pt, cub->map->tile_size, DARK_GREY);
			if (pt.type == 'D')
				paint_square(&cub->img, &pt, cub->map->tile_size, ORANGE);
			row++;
		}
		column++;
	}
}

void	paint_minimap(t_cub *cub)
{
	paint_map(cub);
	// orient_player_cursor(cub);
	// paint_triangle(&cub->img, cub->player.cursor, WHITE);
	paint_square(&cub->img, &cub->player.map_pt, 10, WHITE);
	// rraycasting(cub);
}
