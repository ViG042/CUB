/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 16:03:01 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	project_player_cursor(t_cub	*cub)
{
	cub->player.player_pt.x *= MINIMAP_SCALE;
	cub->player.player_pt.y *= MINIMAP_SCALE;
	cub->player.player_pt.x += MINIMAP_OFFSET - MINIMAP_TILE_SIZE / 2;
	cub->player.player_pt.y += MINIMAP_OFFSET - MINIMAP_TILE_SIZE / 2;
}

void	project_minimap(t_cub *cub)
{
	int		index;

	index = 0;
	cub->minimap = cub->map;
	while (index <= cub->map->size)
	{
		cub->minimap->pts_array[index].x *= MINIMAP_SCALE;
		cub->minimap->pts_array[index].y *= MINIMAP_SCALE;
		cub->minimap->pts_array[index].x += MINIMAP_OFFSET;
		cub->minimap->pts_array[index].y += MINIMAP_OFFSET;
		index++;
	}
	printf("index is %d\n", index);
}

void	project(t_cub *cub)
{
	project_minimap(cub);
	project_player_cursor(cub);
}
