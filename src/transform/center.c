/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:01:04 by mkling            #+#    #+#             */
/*   Updated: 2025/03/04 15:28:30 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* Put the origin of the vector at center of grid */
void	subtract_grid_center(t_pt *point, t_cub *cub)
{
	point->x = point->x - (cub->map->width) / 2;
	point->y = point->y - (cub->map->height) / 2;
}

/* Put the origin of the vector at top left of grid */
void	add_grid_center(t_pt *point, t_cub *cub)
{
	point->x = point->x + (cub->map->width) / 2;
	point->y = point->y + (cub->map->height) / 2;
}

/* Set distance between each points */
void	scale(t_pt *point, t_cub *cub)
{
	point->x = cub->unit * point->x;
	point->y = cub->unit * point->y;
	fprintf(stderr, "zoom is %d\n", cub->zoom);
	point->x *= cub->zoom;
	point->y *= cub->zoom;
	point->z *= cub->zoom;
}

/* Center the grid representation in screen window */
void	center(t_pt *point, t_cub *cub)
{
	point->x += cub->offset_x;
	point->y += cub->offset_y;
}

/*
For point x and y ;
For x_m the middle of the grid width and y_m the middle of the grid height ;
For a the zoom factor ;
For W the width of the window and H the height of the window ;
(a(i - x_m)+ W/2, a(j - y_m) + H /2)
*/
t_pt	apply_zoom_and_offset(t_pt *point, t_cub *cub)
{
	fprintf(stderr, "original is %f, %f, %f\n", point->x, point->y, point->z);
	subtract_grid_center(point, cub);
	fprintf(stderr, "subtract is %f, %f, %f\n", point->x, point->y, point->z);
	scale(point, cub);
	fprintf(stderr, "scale is %f, %f, %f\n", point->x, point->y, point->z);
	center(point, cub);
	fprintf(stderr, "center is %f, %f, %f\n", point->x, point->y, point->z);
	return (*point);
}
