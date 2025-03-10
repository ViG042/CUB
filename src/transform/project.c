/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/10 16:31:57 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pt	project_point(t_cub	*cub, t_pt pt)
{
	(void)cub;
	pt.x *= cub->map->minimap_scale;
	pt.y *= cub->map->minimap_scale;
	pt.x += cub->map->minimap_offset - cub->map->minimap_tile_size / 2;
	pt.y += cub->map->minimap_offset - cub->map->minimap_tile_size / 2;
	return (pt);
}

static void	set_minimap_scale(t_cub *cub)
{
	cub->map->minimap_scale = WIN_WIDTH / 100;
	cub->map->minimap_tile_size = cub->map->minimap_scale - 4;
	cub->map->minimap_offset = 50;
	cub->player.cursor_size = cub->map->minimap_tile_size / 3;
}

void	project_map(t_cub *cub)
{
	set_minimap_scale(cub);
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
