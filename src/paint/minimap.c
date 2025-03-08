/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/03/08 14:35:34 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	paint_miniplayer(t_cub *cub)
{
	cub->player.rgb = WHITE;
	orient_and_paint_player(cub, &cub->player, MINIMAP_TILE_SIZE, WHITE);
}

void	paint_grid(t_cub *cub)
{
	int		index;
	t_pt	pt;

	index = 0;
	while (index <= cub->map->size)
	{
		pt = cub->minimap->pts_array[index];
		if (pt.type == '1')
			paint_square(&cub->img, &pt, MINIMAP_TILE_SIZE, GREY);
		else
			paint_square(&cub->img, &pt, MINIMAP_TILE_SIZE, BLACK);
		index++;
	}
}

void	paint_minimap(t_cub *cub)
{
	paint_grid(cub);
	paint_miniplayer(cub);
}
