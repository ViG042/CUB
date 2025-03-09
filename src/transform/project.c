/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 19:19:48 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pt	project_point(t_cub	*cub, t_pt pt)
{
	(void)cub;
	pt.x *= MINIMAP_SCALE;
	pt.y *= MINIMAP_SCALE;
	pt.x += MINIMAP_OFFSET - MINIMAP_TILE_SIZE / 2;
	pt.y += MINIMAP_OFFSET - MINIMAP_TILE_SIZE / 2;
	return (pt);
}

t_map	*project_minimap(t_cub *cub)
{
	int		index;
	t_map	*minimap;

	index = 0;
	minimap = ft_calloc(sizeof(t_map), 1);
	minimap->pts_array = ft_calloc((cub->map->size) + 1, sizeof(t_pt));
	exit_if(!cub->map->pts_array, MALLOC_FAIL, cub);
	while (index <= cub->map->size)
	{
		minimap->pts_array[index] = cub->map->pts_array[index];
		minimap->pts_array[index].x *= MINIMAP_SCALE;
		minimap->pts_array[index].y *= MINIMAP_SCALE;
		minimap->pts_array[index].x += MINIMAP_OFFSET;
		minimap->pts_array[index].y += MINIMAP_OFFSET;
		index++;
	}
	printf("index is %d\n", index);
	return (minimap);
}

void	project(t_cub *cub)
{
	cub->minimap = project_minimap(cub);
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
