/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/13 12:38:33 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pt	project_point(t_cub	*cub, t_pt pt)
{
	(void)cub;
	pt.x *= cub->map->scale;
	pt.y *= cub->map->scale;
	//pt.x += cub->map->offset_x;// - cub->map->tile_size / 2;
	//pt.y += cub->map->offset_y;// - cub->map->tile_size / 2;
	return (pt);
}

static void	set_minimap_scale(t_cub *cub)
{
	int		minimap_max_height;
	int		minimap_max_width;
	double	scale_width;
	double	scale_height;

	minimap_max_height = WIN_HEIGHT * 0.3;
	minimap_max_width = WIN_WIDTH * 0.3;
	scale_height = (double)minimap_max_height / cub->map->height;
	scale_width = (double)minimap_max_width / cub->map->width;
	cub->map->scale = (int)fmin(scale_height, scale_width);
	cub->map->tile_size = (int)(cub->map->scale);// * 0.9); permet d'afficher les lignes mes cree des decalage dans les deplacements
	cub->map->offset_x = (int)(cub->map->scale);//WIN_WIDTH
	//	- (cub->map->width * cub->map->scale);
	cub->map->offset_y = (int)(cub->map->scale);//WIN_HEIGHT
		//- (cub->map->height * cub->map->scale);//
	cub->player.cursor_size = cub->map->tile_size * 0.2;
}

void	project_map(t_cub *cub)
{
	set_minimap_scale(cub);
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);

}
