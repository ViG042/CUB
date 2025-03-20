/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:06:43 by mkling            #+#    #+#             */
/*   Updated: 2025/03/20 13:44:46 by mkling           ###   ########.fr       */
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
	t_pt	player;
	t_pt	direction;
	t_pt	plane;
	t_pt	camera;
	t_pt	RayDir;
	t_pt	map;
	t_pt	side_dist;
	t_pt	delta_dist;
	double	distance_to_wall;
	int		column;
	int		field_of_view;
	int		side;
	int		hit;
	int		step_x;
	int		step_y;
	int		wall_height;
	int		max_wall_height;
	int		wall_start;
	int		wall_end;

	player = cub->player.grid_pt;
	plane = cub->player.plane;
	max_wall_height = WIN_HEIGHT / 2;
	direction = cub->player.dir;
	column = 0;
	field_of_view = 60;
	while (column < WIN_WIDTH)
	{
		camera.x = 2 * column / (double)WIN_WIDTH - 1;
		// printf("camera is %f\n", camera.x);
		RayDir.x = direction.x + plane.x * camera.x;
		RayDir.y = direction.y + plane.y * camera.x;


		// type of player map tile
		map.x = (int)player.x;
		map.y = (int)player.y;

		// length of ray to one x or y side
		delta_dist.x = 8000;
		delta_dist.y = 8000;
		if (RayDir.x != 0.00)
			delta_dist.x = fabs(1 / RayDir.x);
		if (RayDir.y != 0.00)
			delta_dist.y = fabs(1 / RayDir.y);
		hit = 0;
		// printf("next edge is %f, %f\n", delta_dist.x, delta_dist.y);

		// calculate steps
		if (RayDir.x < 0)
		{
			step_x = -1;
			side_dist.x = (player.x - map.x) * delta_dist.x;
		}
		else
		{
			step_x = 1;
			side_dist.x = (map.x + 1.0 - player.x) * delta_dist.x;
		}
		if (RayDir.y < 0)
		{
			step_y = -1;
			side_dist.y = (player.y - map.y) * delta_dist.y;
		}
		else
		{
			step_y = 1;
			side_dist.y = (map.y + 1.0 - player.y) * delta_dist.y;
		}

		// DDA Algorythm
		while (hit == 0)
		{
			if (side_dist.x < delta_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step_x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step_y;
				side = 1;
			}
			if (camera.x == 0)
				printf("checking map at [%d][%d]\n", (int)map.y, (int)map.x);
			if (cub->map->clean_map[(int)map.y][(int)map.x] == '1')
				hit = 1;
		}
		if (camera.x == 0)
		{
			printf("ray is %f, %f\n", RayDir.x, RayDir.y);
			printf("ray ends at [%f][%f]\n", map.y, map.x);
			trace_ray(cub, cub->player.map_pt, project_point(cub, RayDir), WHITE);
			printf("projected by %d to [%f][%f]\n", cub->map->scale, project_point(cub, map).y, project_point(cub, map).x);
		}

		// Calculate wall distance
		if (side == 0)
			distance_to_wall = (side_dist.x - delta_dist.x);
		else
			distance_to_wall = (side_dist.y - delta_dist.y);



		// calculate wall height
		wall_height = (int)(max_wall_height / distance_to_wall);
		wall_start = -wall_height / 2 + max_wall_height / 2;
		if (wall_start < 0)
			wall_start = 0;
		wall_end = wall_height / 2 + max_wall_height / 2;
		if (wall_start >= max_wall_height)
			wall_start = max_wall_height - 1;

		if (column == WIN_WIDTH / 2)
		{
			printf("distance to wall is %f\n", distance_to_wall);
			printf("wall height is %d\n", wall_height);
		}

		column++;
	}
}







// void	rraycasting(t_cub *cub)
// {
// 	int	ray_count;
// 	int	grid_x;
// 	int	grid_y;
// 	int	dof;
// 	int	side;
// 	t_pt	ray;
// 	t_pt	direction;
// 	t_pt	plane;
// 	t_pt	camera;
// 	t_pt	vertical_hit;
// 	// t_pt	horizontal_hit;
// 	double	ray_angle;
// 	double	x_offset;
// 	double	y_offset;
// 	double	atan;
// 	double	rad_ray_angle;
// 	double	disV;
// 	// double	disH;

// 	ray_angle = cub->player.deg_angle;
// 	if (ray_angle < 0)
// 		ray_angle += 360;
// 	else if (ray_angle >= 360)
// 		ray_angle -= 360;
// 	rad_ray_angle = degree_to_radian(ray_angle);

// 	dof = 0;
// 	side = 0;
// 	ray_count = 0;
// 	x_offset = 0.00;
// 	y_offset = 0.00;

// 	ray = cub->player.grid_pt;
// 	direction.x = -1.00;
// 	direction.y = 0.00;
// 	rotate_direction(&direction, ray_angle);
// 	ray.x += direction.x;
// 	ray.y += direction.y;
// 	printf("angle is %f, with player at %f and %f\n", ray_angle, cub->player.grid_pt.x, cub->player.grid_pt.y);
// 	printf("and ray at at %f and %f\n", ray.x, ray.y);

// 	// CHECK VERTICAL LINES
// 	atan = tan(rad_ray_angle);
// 	disV = 100000;

// 	// If looking left
// 	if (cos(rad_ray_angle) > 0.001)
// 	{
// 		ray.x = (int)cub->player.grid_pt.x + 1.00;
// 		ray.y = (cub->player.grid_pt.x - ray.x) * atan + cub->player.grid_pt.y;
// 		x_offset = 1.00;
// 		y_offset = x_offset * atan;
// 		printf("looking left with ray %f and %f\n", ray.x, ray.y);
// 	}
// 	// If looking right
// 	else if (cos(rad_ray_angle) < -0.001)
// 	{
// 		ray.x = (int)cub->player.grid_pt.x - 0.0001;
// 		ray.y = (cub->player.grid_pt.x - ray.x) * atan + cub->player.grid_pt.y;
// 		x_offset = 1.00;
// 		y_offset = -x_offset * atan;
// 		printf("looking right with ray %f and %f\n", ray.x, ray.y);
// 	}
// 	// If looking up or down
// 	else
// 	{
// 		ray.x = cub->player.grid_pt.x;
// 		ray.y = cub->player.grid_pt.y;
// 		dof = 8;
// 		printf("looking up or down\n");
// 	}
// 	printf("ray x is %f and ray y is %f\n", ray.x, ray.y);
// 	// Seek vertical wall
// 	while (dof < 8)
// 	{
// 		grid_x = (int)(ray.x);
// 		grid_y = (int)(ray.y);

// 		printf("checkin map at map[%d][%d]\n", grid_y, grid_x);
// 		if (grid_x >= 0 && grid_y >= 0 && grid_y < cub->map->height
// 			&& grid_x < cub->map->width)
// 		{
// 			printf("tile is %c\n", cub->map->clean_map[grid_y][grid_x]);
// 			if (cub->map->clean_map[grid_y][grid_x] == '1')
// 			{
// 				dof = 8; // hit wall
// 				disV = cos(rad_ray_angle) * (ray.x - cub->player.grid_pt.x)
// 					- sin(rad_ray_angle) * (ray.y - cub->player.grid_pt.y);
// 			}
// 			else
// 			{
// 				ray.x += x_offset;
// 				ray.y += y_offset;
// 				dof += 1;
// 				// increase by one offset
// 				printf("increasing by offset\n");
// 			}
// 		}
// 		else
// 		{
// 			printf("out of bound, increasing by offset\n");
// 			ray.x += x_offset;
// 			ray.y += y_offset;
// 			dof += 1;
// 			// increase by one offset
// 		}
// 		vertical_hit.x = ray.x;
// 		vertical_hit.y = ray.y;
// 	}
// 	printf("which results in first vertical at %f %f with dof %d and disV %f\n", ray.x, ray.y, dof, disV);
// 	trace_ray(cub, cub->player.map_pt, project_point(cub, vertical_hit), GREEN);

// 	// // CHECK HORIZONTAL LINES
// 	// atan = -1.0 / atan;
// 	// dof = 0;
// 	// disH = 100000;

// 	// // If looking upward
// 	// if (sin(rad_ray_angle) > 0.001)
// 	// {
// 	// 	ray.y = (int)cub->player.grid_pt.y;
// 	// 	ray.x = (cub->player.grid_pt.y - ray.y) * atan + cub->player.grid_pt.x;
// 	// 	y_offset = -1.00;
// 	// 	x_offset = -y_offset * atan;
// 	// }
// 	// // If looking downward
// 	// else if (sin(rad_ray_angle) < -0.001)
// 	// {
// 	// 	ray.y = (int)cub->player.grid_pt.y + 1.00;
// 	// 	ray.x = (cub->player.grid_pt.y - ray.y) * atan + cub->player.grid_pt.x;
// 	// 	y_offset = 1.00;
// 	// 	x_offset = -y_offset * atan;
// 	// }
// 	// // If looking left or right
// 	// else
// 	// {
// 	// 	ray.x = cub->player.grid_pt.x;
// 	// 	ray.y = cub->player.grid_pt.y;
// 	// 	dof = 8;
// 	// }
// 	// // seek horizontal wall
// 	// while (dof < 8)
// 	// {
// 	// 	grid_x = (int)(ray.x) >> 6;
// 	// 	grid_y = (int)(ray.y) >> 6;
// 	// 	printf("checkin map at map[%d][%d]\n", grid_y, grid_x);
// 	// 	if (grid_x >= 0 && grid_y >= 0 && grid_y < cub->map->height
// 	// 		&& grid_x < cub->map->width)
// 	// 	{
// 	// 		printf("tile is %c\n", cub->map->clean_map[grid_y][grid_x]);
// 	// 		if (cub->map->clean_map[grid_y][grid_x] == '1')
// 	// 		{
// 	// 			dof = 8; // hit wall
// 	// 			disV = cos(rad_ray_angle) * (ray.x - cub->player.grid_pt.x)
// 	// 				- sin(rad_ray_angle) * (ray.y - cub->player.grid_pt.y);
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			ray.x += x_offset;
// 	// 			ray.y += y_offset;
// 	// 			dof += 1;
// 	// 			// increase by one offset
// 	// 		}
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		ray.x += x_offset;
// 	// 		ray.y += y_offset;
// 	// 		dof += 1;
// 	// 		// increase by one offset
// 	// 	}
// 	// 	horizontal_hit.x = ray.x;
// 	// 	horizontal_hit.y = ray.y;
// 	// }
// 	// printf("which results in first horizontal at %f %f with dof %d and disH %f\n", ray.x, ray.y, dof, disH);


// 	// trace_ray(cub, cub->player.map_pt, project_point(cub, ray), ORANGE);
// }

