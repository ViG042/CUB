/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/10 17:07:29 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pt	project_point(t_cub	*cub, t_pt pt)
{
	(void)cub;
	pt.x *= cub->map->scale;
	pt.y *= cub->map->scale;
	pt.x += cub->map->offset_x - cub->map->tile_size / 2;
	pt.y += cub->map->offset_y - cub->map->tile_size / 2;
	return (pt);
}

static void	set_minimap_scale(t_cub *cub)
{
	int		minimap_max_height;
	int		minimap_max_width;
	float	scale_width;
	float	scale_height;

	minimap_max_height = WIN_HEIGHT * 0.5;
	minimap_max_width = WIN_WIDTH * 0.5;
	scale_height = (float)minimap_max_height / cub->map->height;
	scale_width = (float)minimap_max_width / cub->map->width;
	cub->map->scale = (int)fmin(scale_height, scale_width);
	cub->map->tile_size = (int)(cub->map->scale * 0.9);
	cub->map->offset_x = WIN_WIDTH
		- (cub->map->width * cub->map->scale);
	cub->map->offset_y = WIN_HEIGHT
		- (cub->map->height * cub->map->scale);
	cub->player.cursor_size = cub->map->tile_size * 0.3;
}

void	project_map(t_cub *cub)
{
	set_minimap_scale(cub);
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
