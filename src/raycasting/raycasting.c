/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:06:43 by mkling            #+#    #+#             */
/*   Updated: 2025/03/18 17:46:30 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_lline(t_line *line, t_cub *cub)
{
	line->current = line->start;
	while (is_in_window(line->current.x, line->current.y))
	{
		paint_point(&cub->img, &line->current, ORANGE);
		line->error2 = 2 * line->error;
		if (line->error2 >= line->delta.y)
		{
			if ((int)line->current.x == (int)line->end.x)
				break ;
			line->error += line->delta.y;
			line->current.x += line->sign.x;
		}
		if (line->error2 <= line->delta.x)
		{
			if ((int)line->current.y == (int)line->end.y)
				break ;
			line->error += line->delta.x;
			line->current.y += line->sign.y;
		}
	}
}

void	paint_lline(t_pt start, t_pt end, t_cub *cub)
{
	t_line	line;

	line.end = end;
	line.start = start;
	line.sign.x = 1.0;
	line.sign.y = 1.0;
	line.delta.x = ft_abs(line.end.x - line.start.x);
	if (line.start.x > line.end.x)
		line.sign.x = -1.0;
	line.delta.y = -ft_abs(line.end.y - line.start.y);
	if (line.start.y > line.end.y)
		line.sign.y = -1.0;
	print_lline(&line, cub);
}

void	rraycasting(t_cub *cub)
{
	int	ray_count;
	// int	grid_x;
	// int	grid_y;
	// int	mp;
	int	dof;
	t_pt	ray;
	t_pt	direction;
	double	ray_angle;
	double	x_offset;
	double	y_offset;
	double	atan;

	ray_angle = cub->player.player_angle;
	if (ray_angle < 0)
		ray_angle += 360;
	else if (ray_angle >= 360)
		ray_angle -= 360;

	dof = 0;
	ray_count = 0;
	x_offset = 0.00;
	y_offset = 0.00;

	printf("RAYCASTING\n");
	ray = cub->player.grid_pt;
	direction.x = 0;
	direction.y = 5;
	rotate_direction(&direction, ray_angle);
	ray.x += direction.x;
	ray.y += direction.y;
	printf("angle is %f, with player at %f and %f\n", ray_angle, cub->player.map_pt.x, cub->player.map_pt.y);
	printf("and ray at at %f and %f\n", ray.x, ray.y);

	paint_lline(cub->player.map_pt, project_point(cub, ray), cub);

	// CHECK VERTICAL LINES
	atan = tan(ray_angle);

	// If looking left
	if (ray_angle > 180)
	{
		ray.x = (int)cub->player.grid_pt.x;
		ray.y = (cub->player.grid_pt.x - ray.x) * atan + cub->player.grid_pt.y;
		x_offset = 1.00;
		y_offset = -x_offset * atan;
	}
	// If looking right
	else if (ray_angle < 180)
	{
		ray.y = (int)cub->player.grid_pt.x;
		ray.x = (cub->player.grid_pt.x - ray.x) * atan + cub->player.grid_pt.y;
		y_offset = -1.00;
		x_offset = -x_offset * atan;
	}
	// If looking up or down
	else
	{
		ray.x = cub->player.grid_pt.x;
		ray.y = cub->player.grid_pt.y;
		dof = 8;
	}
	// printf("ray x is %f and ray y is %f\n", ray.x, ray.y);
	// Seek vertical wall
	// while (dof < 8)
	// {
	// 	grid_x = (int)(ray_x);
	// 	grid_y = (int)(ray_y);
	// 	mp = grid_y * cub->map->width + grid_x;
	// 	if (grid_x > 0 && grid_y > 0
	// 		&& cub->map->clean_map[grid_y]
	// 		&& cub->map->clean_map[grid_y][grid_x]
	// 		&& cub->map->clean_map[grid_y][grid_x] == 1)
	// 		dof = 8; // hit wall
	// 	else
	// 	{
	// 		ray_x += x_offset;
	// 		ray_y += y_offset;
	// 		dof += 1;
	// 		// increase by one offset
	// 	}
	// }
	// printf("which results in first vertical at %f %f with dof %d\n", ray.x, ray.y, dof);

	// CHECK HORIZONTAL LINES
	atan = -1 / atan;

	// If looking upward
	if (ray_angle > PI)
	{
		ray.y = (int)cub->player.grid_pt.y;
		ray.x = (cub->player.grid_pt.y - ray.y) * atan + cub->player.grid_pt.x;
		y_offset = -1.00;
		x_offset = -y_offset * atan;
	}
	// If looking downward
	else if (ray_angle < PI)
	{
		ray.y = (int)cub->player.grid_pt.y;
		ray.x = (cub->player.grid_pt.y - ray.y) * atan + cub->player.grid_pt.x;
		y_offset = 1.00;
		x_offset = -y_offset * atan;
	}
	// If looking left or right
	else
	{
		ray.x = cub->player.grid_pt.x;
		ray.y = cub->player.grid_pt.y;
		dof = 8;
	}
	// seek horizontal wall
	// while (dof < 8)
	// {
	// 	grid_x = (int)(ray_x) >> 6;
	// 	grid_y = (int)(ray_y) >> 6;
	// 	mp = grid_y * cub->map->width + grid_x;
	// 	if (mp < cub->map->width * cub->map->height && cub->map->clean_map[grid_y][grid_x] == 1)
	// 		dof = 8; // hit wall
	// 	else
	// 	{
	// 		ray_x += x_offset;
	// 		ray_y += y_offset;
	// 		dof += 1;
	// 		// increase by one offset
	// 	}
	// }
	// printf("which results in first horizontal at %f %f with dof %d\n", ray.x, ray.y, dof);


}

