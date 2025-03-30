/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/30 21:18:35 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pt	normalize_vector(t_pt *point)
{
	t_pt	unit_vector;
	float	magnitude;

	unit_vector = *point;
	magnitude = sqrt(point->x * point->x + point->y * point->y);
	if (magnitude != 0)
		unit_vector.x /= magnitude;
	if (point->y != 0)
		unit_vector.y /= magnitude;
	return (unit_vector);
}

void	rotate_point(t_cub *cub, t_pt *point, t_pt *center, float angle)
{
	float	radian;
	float	cos_angle;
	float	sin_angle;
	t_pt	centered;
	t_pt	rotated;

	(void)cub;
	centered.x = point->x - center->x;
	centered.y = point->y - center->y;
	radian = angle * RADIAN;
	cos_angle = cos(radian);
	sin_angle = sin(radian);
	rotated.x = cos_angle * centered.x - sin_angle * centered.y;
	rotated.y = sin_angle * centered.x + cos_angle * centered.y;
	point->x = rotated.x + center->x;
	point->y = rotated.y + center->y;
}

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
	float	scale_width;
	float	scale_height;

	minimap_max_height = WIN_HEIGHT * MINIMAP_PROPORTION * 0.7;
	minimap_max_width = WIN_WIDTH * MINIMAP_PROPORTION * 0.7;
	scale_height = (float)minimap_max_height / cub->map->height;
	scale_width = (float)minimap_max_width / cub->map->width;
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
