#include "cub.h"

void	init_first_dist(t_cub *cub)
{
	double	x;
	double	y;

	x = cub->player.grid_pt.x;
	y = cub->player.grid_pt.y;
	if (cub->ray.angle_deg < 90)
	{
		cub->ray.firstx = (ceil(x) - x);
		cub->ray.firsty = (floor(y) - y);
	}
	else if (cub->ray.angle_deg < 180)
	{
		cub->ray.firstx = (ceil(x) - x);
		cub->ray.firsty = (ceil(y) - y);
	}
	else if (cub->ray.angle_deg < 270)
	{
		cub->ray.firstx = (floor(x) - x);
		cub->ray.firsty = (ceil(y) - y);
	}
	else
	{
		cub->ray.firstx = (floor(x) - x);
		cub->ray.firsty = (floor(y) - y);
	}
}

/*1st ligne gives a value from -1 to 1
2ng line give a value in degrees from -30 to 30 for a field of view of 60
3rd ligne corrects angle accordig to actual angle of the player*/
void	init_ray(t_cub *cub, int pixel_column)
{
	double	angle;

	angle = 2 * pixel_column / (double)WIN_WIDTH - 1;
	angle = angle * FIELD_OF_VIEW / 2;
	angle = angle + cub->player.player_angle;
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	cub->ray.angle_deg = angle;
	cub->ray.angle_rad = fabs(angle * (PI / 180.0));
	if (sin(cub->ray.angle_rad) == 0.0)
		cub->ray.dist_x = 100;
	else
		cub->ray.dist_x = fabs(1 / sin(cub->ray.angle_rad));
	if (cos(cub->ray.angle_rad) == 0.0)
		cub->ray.dist_y = 100;
	else
		cub->ray.dist_y = fabs(1 / cos(cub->ray.angle_rad));
	init_first_dist(cub);
}

void	init_step(t_cub *cub)
{
	cub->ray.x = floor(cub->player.grid_pt.x);
	cub->ray.y = floor(cub->player.grid_pt.y);
	cub->ray.step_x = 1;
	cub->ray.step_y = 1;
	if (cub->ray.firstx < 0)
		cub->ray.step_x = -1;
	if (cub->ray.firsty < 0)
		cub->ray.step_y = -1;
	cub->ray.firstx = cub->ray.firstx * cub->ray.dist_x;
	cub->ray.firsty = cub->ray.firsty * cub->ray.dist_y;
}

void	digital_differential_analyser(t_cub *cub)
{
	cub->ray.dda_x = fabs((double)cub->ray.firstx);
	cub->ray.dda_y = fabs((double)cub->ray.firsty);
	while (cub->map->clean_map[cub->ray.y][cub->ray.x] == '0')
	{
		if (fabs(cub->ray.dda_x) < fabs(cub->ray.dda_y))
		{
			cub->ray.side = LEFT;
			cub->ray.x += cub->ray.step_x;
			cub->ray.dda_x += cub->ray.dist_x;
		}
		else
		{
			cub->ray.side = TOP;
			cub->ray.y += cub->ray.step_y;
			cub->ray.dda_y += cub->ray.dist_y;
		}
	}
}

void	define_surface_collision(t_cub *cub)
{
	if (cub->ray.angle_deg < 90)
	{
		if (cub->ray.side == TOP)
			cub->ray.side = NORTH;
		else
			cub->ray.side = EAST;
	}
	else if (cub->ray.angle_deg < 180)
	{
		if (cub->ray.side == TOP)
			cub->ray.side = SOUTH;
		else
			cub->ray.side = EAST;
	}
	else if (cub->ray.angle_deg < 270)
	{
		if (cub->ray.side == TOP)
			cub->ray.side = SOUTH;
		else
			cub->ray.side = WEST;
	}
	else
	{
		if (cub->ray.side == TOP)
			cub->ray.side = NORTH;
		else
			cub->ray.side = WEST;
	}
}

void	calculate_dist_to_wall(t_cub *cub)
{
	if (cub->ray.side == NORTH || cub->ray.side == SOUTH)
		cub->ray.wall_dist = fabs(fabs(cub->ray.dda_y) - fabs(cub->ray.dist_y));
	else
		cub->ray.wall_dist = fabs(fabs(cub->ray.dda_x) - fabs(cub->ray.dist_x));
}

void	calculate_wall_height(t_cub *cub)
{
	cub->ray.wall_height = (int)(WIN_HEIGHT / cub->ray.wall_dist);
	cub->ray.top_wall = (WIN_HEIGHT - cub->ray.wall_height) / 2;
	if (cub->ray.top_wall < 0)
		cub->ray.top_wall = 0;
	cub->ray.end_wall = cub->ray.top_wall + cub->ray.wall_height;
	if (cub->ray.end_wall >= WIN_HEIGHT)
		cub->ray.end_wall = WIN_HEIGHT;
}

/*pixel column from 0 to WIN_WIDTH*/
void	raycasting(t_cub *cub)
{
	int		column;

	column = 0;
	while (column++ < WIN_WIDTH)
	{
		init_ray(cub, column);
		init_step(cub);
		digital_differential_analyser(cub);
		define_surface_collision(cub);
		calculate_dist_to_wall(cub);
		calculate_wall_height(cub);
		begug_print(cub, column);
		paint_column(cub, column);
	}
}

