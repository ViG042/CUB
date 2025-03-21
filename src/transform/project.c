/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/21 01:11:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*	//pt.x += cub->map->offset_x;// - cub->map->tile_size / 2;
	//pt.y += cub->map->offset_y;// - cub->map->tile_size / 2;*/
t_pt	project_point(t_cub	*cub, t_pt pt)
{
	(void)cub;
	pt.x *= cub->map->scale;
	pt.y *= cub->map->scale;
	return (pt);
}

/*simplified cub->map->tile_size
// * 0.9); permet d'afficher les lignes mais
 cree des decalage dans les deplacements
simplified cub->map->offset_x
//WIN_WIDTH//	- (cub->map->width * cub->map->scale);
simplified cub->map->offset_y
//WIN_HEIGHT//- (cub->map->height * cub->map->scale);//*/
static void	set_minimap_scale(t_cub *cub)
{
	int		minimap_max_height;
	int		minimap_max_width;
	double	scale_width;
	double	scale_height;

	minimap_max_height = WIN_HEIGHT * MINIMAP_PROPORTION * 0.7;
	minimap_max_width = WIN_WIDTH * MINIMAP_PROPORTION * 0.7;
	scale_height = (double)minimap_max_height / cub->map->height;
	scale_width = (double)minimap_max_width / cub->map->width;
	cub->map->scale = (int)fmin(scale_height, scale_width);
	cub->map->tile_size = (int)(cub->map->scale);
	cub->map->offset_x = (int)(cub->map->scale);
	cub->map->offset_y = (int)(cub->map->scale);
	cub->player.cursor_size = cub->map->tile_size * 0.8;
}

void	project_map(t_cub *cub)
{
	set_minimap_scale(cub);
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
