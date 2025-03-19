/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:06:43 by mkling            #+#    #+#             */
/*   Updated: 2025/03/19 12:01:00 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	degree_to_radian(double degree_angle)
{
	return (degree_angle * RADIAN);
}

void	print_ray(t_cub *cub, t_line *line, int color)
{
	line->current = line->start;
	while (is_in_window(line->current.x, line->current.y))
	{
		paint_point(&cub->img, &line->current, color);
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

void	trace_ray(t_cub *cub, t_pt start, t_pt end, int color)
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
	print_ray(cub, &line, color);
}

void	rraycasting(t_cub *cub)
{
	int	ray_count;
	int	grid_x;
	int	grid_y;
	int	dof;
	t_pt	ray;
	t_pt	direction;
	t_pt	vertical_hit;
	t_pt	horizontal_hit;
	double	ray_angle;
	double	x_offset;
	double	y_offset;
	double	atan;
	double rad_ray_angle;

	ray_angle = cub->player.player_angle;
	if (ray_angle < 0)
		ray_angle += 360;
	else if (ray_angle >= 360)
		ray_angle -= 360;
	rad_ray_angle = degree_to_radian(ray_angle);

	dof = 0;
	ray_count = 0;
	x_offset = 0.00;
	y_offset = 0.00;

	printf("RAYCASTING\n");
	ray = cub->player.grid_pt;
	direction.x = 0;
	direction.y = -5;
	rotate_direction(&direction, ray_angle);
	ray.x += direction.x;
	ray.y += direction.y;
	printf("angle is %f, with player at %f and %f\n", ray_angle, cub->player.grid_pt.x, cub->player.grid_pt.y);
	printf("and ray at at %f and %f\n", ray.x, ray.y);

	trace_ray(cub, cub->player.map_pt, project_point(cub, ray), WHITE);


	// CHECK VERTICAL LINES
	atan = tan(rad_ray_angle);

	// If looking left
	if (cos(rad_ray_angle) > 0.001)
	{
		ray.x = (int)cub->player.grid_pt.x;
		ray.y = (cub->player.grid_pt.x - ray.x) * atan + cub->player.grid_pt.y;
		x_offset = 1.00;
		y_offset = x_offset * atan;
		printf("looking left with ray %f and %f\n", ray.x, ray.y);
	}
	// If looking right
	else if (cos(rad_ray_angle) < -0.001)
	{
		ray.x = (int)cub->player.grid_pt.x - 0.0001;
		ray.y = (cub->player.grid_pt.x - ray.x) * atan + cub->player.grid_pt.y;
		x_offset = -1.00;
		y_offset = -x_offset * atan;
		printf("looking right with ray %f and %f\n", ray.x, ray.y);
	}
	// If looking up or down
	else
	{
		ray.x = cub->player.grid_pt.x;
		ray.y = cub->player.grid_pt.y;
		dof = 8;
		printf("looking up or down\n");
	}
	printf("ray x is %f and ray y is %f\n", ray.x, ray.y);
	// Seek vertical wall
	while (dof < 8)
	{
		grid_x = (int)(ray.x);
		grid_y = (int)(ray.y);

		printf("checkin map at map[%d][%d]\n", grid_y, grid_x);
		if (grid_x < 0 || grid_y < 0 || grid_y > cub->map->height - 1
			|| grid_x > (int)ft_strlen(cub->map->clean_map[grid_y] - 1))
			dof = 8;
		else if (cub->map->clean_map[grid_y][grid_x] == '1')
			dof = 8; // hit wall
		else
		{
			ray.x += x_offset;
			ray.y += y_offset;
			dof += 1;
			// increase by one offset
		}
		vertical_hit.x = ray.x;
		vertical_hit.y = ray.y;
	}
	printf("which results in first vertical at %f %f with dof %d\n", ray.x, ray.y, dof);
	// trace_ray(cub, cub->player.map_pt, project_point(cub, ray), GREEN);

	// CHECK HORIZONTAL LINES
	atan = -1.0 / atan;
	dof = 0;

	// If looking upward
	if (sin(rad_ray_angle) > 0.001)
	{
		ray.y = (int)cub->player.grid_pt.y;
		ray.x = (cub->player.grid_pt.y - ray.y) * atan + cub->player.grid_pt.x;
		y_offset = -1.00;
		x_offset = -y_offset * atan;
	}
	// If looking downward
	else if (sin(rad_ray_angle) < -0.001)
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
	while (dof < 8)
	{
		grid_x = (int)(ray.x);
		grid_y = (int)(ray.y);
		if (grid_x < 0 || grid_y < 0 || grid_y > cub->map->height - 1
			|| grid_x > (int)ft_strlen(cub->map->clean_map[grid_y]) - 1)
			dof = 8;
		else if (cub->map->clean_map[grid_y][grid_x] == '1')
			dof = 8; // hit wall
		else
		{
			ray.x += x_offset;
			ray.y += y_offset;
			dof += 1;
			// increase by one offset
		}
		horizontal_hit.x = ray.x;
		horizontal_hit.y = ray.y;
	}
	printf("which results in first horizontal at %f %f with dof %d\n", ray.x, ray.y, dof);


	// trace_ray(cub, cub->player.map_pt, project_point(cub, ray), ORANGE);
}

