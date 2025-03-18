#include "cub.h"

void	init_first_dist(t_cub *cub, double *ray)
{
	double	x;
	double	y;

	x = cub->player.grid_pt.x;
	y = cub->player.grid_pt.y;
	if (ray[ANGLE_DEG] < 90)
	{
		ray[FIRST_X] = (ceil(x) - x) * ray[DIST_X];
		ray[FIRST_Y] = (floor(y) - y) * ray[DIST_Y];
	}
	else if (ray[ANGLE_DEG] < 180)
	{
		ray[FIRST_X] = (ceil(x) - x) * ray[DIST_X];
		ray[FIRST_Y] = (ceil(y) - y) * ray[DIST_Y];
	}
	else if (ray[ANGLE_DEG] < 270)
	{
		ray[FIRST_X] = (floor(x) - x) * ray[DIST_X];
		ray[FIRST_Y] = (ceil(y) - y) * ray[DIST_Y];
	}
	else
	{
		ray[FIRST_X] = (floor(x) - x) * ray[DIST_X];
		ray[FIRST_Y] = (floor(y) - y) * ray[DIST_Y];
	}
}

/*1st ligne gives a value from -1 to 1
2ng line give a value in degrees from -30 to 30 for a field of view of 60
3rd ligne corrects angle accordig to actual angle of the player*/
void	init_ray(t_cub *cub, int pixel_column, double *ray)
{
	double	angle;

	angle = 2 * (pixel_column / (double)WIN_WIDTH) - 1;
	angle = angle * FIELD_OF_VIEW / 2;
	angle = angle + cub->player.player_angle;
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	ray[ANGLE_DEG] = angle;
	ray[ANGLE_RAD] = fabs(angle * (PI / 180.0));
	ray[DIST_X] = fabs(1 / sin(ray[ANGLE_RAD]));
	ray[DIST_Y] = fabs(1 / cos(ray[ANGLE_RAD]));
	init_first_dist(cub, ray);
	if (ray[FIRST_X] < 0)
		ray[DIST_X] *= -1;
	if (ray[FIRST_Y] < 0)
		ray[DIST_Y] *= -1;
}


void	init_step(t_cub *cub, double *ray, int *step)
{
	step[X] = floor(cub->player.grid_pt.x);
	step[Y] = floor(cub->player.grid_pt.y);
	step[STEP_X] = 1;
	step[STEP_Y] = 1;
	if (ray[FIRST_X] < 0)
		step[STEP_X] = -1;
	if (ray[FIRST_Y] < 0)
		step[STEP_Y] = -1;
}

/*
In the if and else, we will put some condition
to know from where the block is hit (N S W E)*/
void	digital_differential_analyser(t_cub *cub, double *ray, int *step, int pixel_column)
{
	double	dda_x;
	double	dda_y;

	(void)pixel_column;
	dda_x = fabs(ray[FIRST_X]);
	dda_y = fabs(ray[FIRST_Y]);
	while (cub->map->clean_map[step[Y]][step[X]] == '0')
	{
		if (dda_x < dda_y)
		{
			step[X] += step[STEP_X];
			dda_x += ray[DIST_X];
		}
		else
		{
			step[Y] += step[STEP_Y];
			dda_y += ray[DIST_Y];
		}
	}
}

void	calculate_dist_to_wall(t_cub *cub, double *ray, int *step)
{
	(void)cub;
	if (fabs(ray[DIST_X]) < fabs(ray[DIST_Y]))
		ray[DIST_TO_WALL] = fabs(ray[FIRST_X]) + abs(step[X]) * fabs(ray[DIST_X]);
	else
		ray[DIST_TO_WALL] = fabs(ray[FIRST_Y]) + abs(step[Y]) * fabs(ray[DIST_Y]);
}

void	calculate_wall_height(double *ray, int *step)
{
	double	min;
	double	max;
	int	int_height;

	min = 0.2;
	max = 20.0;
	// if ((ray[DIST_TO_WALL]) <= min)
	// 	int_height = WIN_HEIGHT;
	// else if ((ray[DIST_TO_WALL]) > max)
	// 	int_height = 0;
	// else
	// {
		int_height = (int)(((max - ray[DIST_TO_WALL]) / max) * WIN_HEIGHT);
	// }
	step[FIRST_PIXEL] = (WIN_HEIGHT - int_height) / 2;
	step[LAST_PIXEL] = step[FIRST_PIXEL] + int_height;
	step[HEIGHT] = int_height;
}

/*pixel column from 0 to WIN_WIDTH*/
void	raycasting(t_cub *cub)
{
	int		pixel_column;
	double	ray[9];
	int		step[7];

	pixel_column = 0;
	while (pixel_column++ < WIN_WIDTH)
	{
		init_ray(cub, pixel_column, ray);
		init_step(cub, ray, step);

		// if (pixel_column == WIN_WIDTH / 2)
		// 			printf("pixel_column=[%d] angle_deg=[%f] angle_rad=[%f] \
		// composante_x=[%f] composante_y=[%f] first_x[%f] first_y=[%f] \
		// X=[%d] Y=[%d] STEP_X=[%d] STEP_Y=[%d]\n",
		// 				pixel_column, ray[ANGLE_DEG], ray[ANGLE_RAD],
		// 				ray[DIST_X], ray[DIST_Y], ray[FIRST_X], ray[FIRST_Y],
		// 				step[X], step[Y], step[STEP_X], step[STEP_Y]);
		digital_differential_analyser(cub, ray, step, pixel_column);

		calculate_dist_to_wall(cub, ray, step);

		calculate_wall_height(ray, step);

		// if (pixel_column == WIN_WIDTH / 2)
		// {
		// 	printf("wall hit at X=[%d] Y=[%d]\n", step[X], step[Y]);
		// 	printf("DIST_X=[%f] Y=[%f]\n", ray[FIRST_X], ray[FIRST_Y]);
		// 	printf("ray[DIST_TO_WALL]=[%f]\n\n", ray[DIST_TO_WALL]);///
		// }

		if (pixel_column == WIN_WIDTH / 2)
		{
			printf("ray[DIST_TO_WALL]=[%f]\n", ray[DIST_TO_WALL]);///
			printf("height=[%d]\n\n", step[HEIGHT]);
		}

		int c = step[FIRST_PIXEL];
		while (c < step[LAST_PIXEL])
		{
			paint_pixel(&cub->img, pixel_column, c, ORANGE);
			c++;
		}
		//ray[STOP_PAINT] = calculate_wall_height(cub, ray[DIST_TO_WALL], STOP_PAINT);
		//paint(cub, pixel_column, ray[START_PAINT], ray[STOP_PAINT]);
	}
}
