#include "cub.h"

void	init_first_dist(t_cub *cub, double *ray)
{
	double	x;
	double	y;

	x = cub->player.grid_pt.x;
	y = cub->player.grid_pt.y;
	if (ray[ANGLE_DEG] < 90)
	{
		ray[F_X] = (ceil(x) - x);
		ray[F_Y] = (floor(y) - y);
	}
	else if (ray[ANGLE_DEG] < 180)
	{
		ray[F_X] = (ceil(x) - x);
		ray[F_Y] = (ceil(y) - y);
	}
	else if (ray[ANGLE_DEG] < 270)
	{
		ray[F_X] = (floor(x) - x);
		ray[F_Y] = (ceil(y) - y);
	}
	else
	{
		ray[F_X] = (floor(x) - x);
		ray[F_Y] = (floor(y) - y);
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
	step[X_PLAYER] = floor(cub->player.grid_pt.x);
	step[Y_PLAYER] = floor(cub->player.grid_pt.y);
	step[X] = step[X_PLAYER];
	step[Y] = step[Y_PLAYER];
	step[STEP_X] = 1;
	step[STEP_Y] = 1;
	if (ray[F_X] < 0)
		step[STEP_X] = -1;
	if (ray[F_Y] < 0)
		step[STEP_Y] = -1;
	ray[FIRST_X] = ray[F_X] * ray[DIST_X];
	ray[FIRST_Y] = ray[F_Y] * ray[DIST_Y];
}

/*
In the if and else, we will put some condition
to know from where the block is hit (N S W E)*/
void	digital_differential_analyser(t_cub *cub, double *ray, int *step, int pixel_column)
{
	double	dda_x;
	double	dda_y;

	(void)pixel_column;
	(void)cub;
	dda_x = fabs(ray[FIRST_X]);
	dda_y = fabs(ray[FIRST_Y]);
	while (cub->map->clean_map[step[Y]][step[X]] == '0')
	{
		if (fabs(dda_x) < fabs(dda_y))
		{
			step[LAST_MOVE] = LEFT;
			step[X] += step[STEP_X];
			dda_x += ray[DIST_X];
		}
		else
		{
			step[LAST_MOVE] = TOP;
			step[Y] += step[STEP_Y];
			dda_y += ray[DIST_Y];
		}
	}
}


void	define_surface_collision (double *ray, int *step)
{
	if (ray[ANGLE_DEG] < 90)
	{
		if (step[LAST_MOVE] == TOP)
			step[LAST_MOVE] = NORTH;
		else
			step[LAST_MOVE] = EAST;
	}
	else if (ray[ANGLE_DEG] < 180)
	{
		if (step[LAST_MOVE] == TOP)
			step[LAST_MOVE] = SOUTH;
		else
			step[LAST_MOVE] = EAST;
	}
	else if (ray[ANGLE_DEG] < 270)
	{
		if (step[LAST_MOVE] == TOP)
			step[LAST_MOVE] = SOUTH;
		else
			step[LAST_MOVE] = WEST;
	}
	else
	{
		if (step[LAST_MOVE] == TOP)
			step[LAST_MOVE] = NORTH;
		else
			step[LAST_MOVE] = WEST;
	}
}

void	calculate_angle_90(double *ray, int *step, int pixel_column)
{
	if (step[LAST_MOVE] == NORTH)
	{
		if (ray[ANGLE_DEG] >= 270)
			ray[ANGLE_90] = 360 - ray[ANGLE_DEG];
		else
			ray[ANGLE_90] = ray[ANGLE_DEG];
	}
	if (step[LAST_MOVE] == SOUTH)
	{
		if (ray[ANGLE_DEG] >= 180)
			ray[ANGLE_90] = ray[ANGLE_DEG] - 180;
		else
			ray[ANGLE_90] = 180 - ray[ANGLE_DEG];
	}
	if (step[LAST_MOVE] == WEST)
	{
		if (ray[ANGLE_DEG] >= 270)
			ray[ANGLE_90] = ray[ANGLE_DEG] - 270;
		else
			ray[ANGLE_90] = 270 - ray[ANGLE_DEG];
	}
	if (step[LAST_MOVE] == EAST)
	{
		if (ray[ANGLE_DEG] >= 90)
			ray[ANGLE_90] = ray[ANGLE_DEG] - 90;
		else
			ray[ANGLE_90] = 90 - ray[ANGLE_DEG];
	}

	if (pixel_column == WIN_WIDTH / 2)
	{
		printf("ray[ANGLE_90] = [%f]\n", ray[ANGLE_90]);
	}
}

void	calculate_dist_to_wall(t_cub *cub, double *ray, int *step, int pixel_column)
{
	(void)cub;
	(void)pixel_column;

	ray[DIST_TO_WALL_X] = 0;
	ray[DIST_TO_WALL_Y] = 0;

	if (pixel_column == WIN_WIDTH / 2)
	{
		printf("last move = [%d]\n", step[LAST_MOVE]);
		printf("fabs(ray[F_Y])=[%f] + abs(step[Y]=[%d] - step[Y_PLAYER]=[%d]) - 1\n", fabs(ray[F_Y]), step[Y], step[Y_PLAYER]);
		printf("fabs(ray[F_X])=[%f] + abs(step[X]=[%d] - step[X_PLAYER]=[%d]) - 1\n", fabs(ray[F_X]), step[X], step[X_PLAYER]);
	}

	if (step[LAST_MOVE] == NORTH || step[LAST_MOVE] == SOUTH)
	{
		ray[DIST_TO_WALL_Y] = (fabs(ray[F_Y]) + abs(step[Y] - step[Y_PLAYER]) -1);
		ray[DIST_TO_WALL] = fabs(ray[DIST_TO_WALL_Y] / cos(ray[ANGLE_90] * (PI / 180.0)));
	}
	else
	{
		ray[DIST_TO_WALL_X] = (fabs(ray[F_X]) + abs(step[X] - step[X_PLAYER]) -1);
		ray[DIST_TO_WALL] = fabs(ray[DIST_TO_WALL_X] / cos(ray[ANGLE_90] * (PI / 180.0)));
	}


	if (pixel_column == WIN_WIDTH / 2)
	{
		printf("DIST_TO_WALL_X=[%f]\n", ray[DIST_TO_WALL_X]);
		printf("DIST_TO_WALL_Y=[%f]\n", ray[DIST_TO_WALL_Y]);
		printf("DIST_TO_WALL=[%f]\n", ray[DIST_TO_WALL]);
	}
}

void	calculate_wall_height(double *ray, int *step)
{
	double	min;
	double	max;
	int	int_height;

	min = 0.2;
	max = 10.0;

	int_height = (int)(((max - ray[DIST_TO_WALL]) / max) * WIN_HEIGHT);

	step[FIRST_PIXEL] = (WIN_HEIGHT - int_height) / 2;
	step[LAST_PIXEL] = step[FIRST_PIXEL] + int_height;
	step[HEIGHT] = int_height;
}

/*pixel column from 0 to WIN_WIDTH*/
void	raycasting(t_cub *cub)
{
	int		pixel_column;
	double	ray[12];
	int		step[10];

	pixel_column = 0;
	while (pixel_column++ < WIN_WIDTH)
	{
		// if (pixel_column % 10 == 0)
		// {
		init_ray(cub, pixel_column, ray);
		init_step(cub, ray, step);

// 		if (pixel_column == WIN_WIDTH / 2)
// 			printf("pixel_column=[%d] angle_deg=[%f] angle_rad=[%f] \
// composante_x=[%f] composante_y=[%f] first_x[%f] first_y=[%f] \
// X=[%d] Y=[%d] STEP_X=[%d] STEP_Y=[%d]\n",
// 				pixel_column, ray[ANGLE_DEG], ray[ANGLE_RAD],
// 				ray[DIST_X], ray[DIST_Y], ray[FIRST_X], ray[FIRST_Y],
// 				step[X], step[Y], step[STEP_X], step[STEP_Y]);
		digital_differential_analyser(cub, ray, step, pixel_column);

		define_surface_collision(ray, step);

		calculate_angle_90(ray, step, pixel_column);

		calculate_dist_to_wall(cub, ray, step, pixel_column);

		//ray[DIST_TO_WALL] *= fabs(cos(ray[ANGLE_RAD] - cub->player.player_angle));

		calculate_wall_height(ray, step);

		if (pixel_column == WIN_WIDTH / 2)
		{
			printf("wall hit at X=[%d] Y=[%d]\n", step[X], step[Y]);
			//printf("DIST_X=[%f] Y=[%f]\n", ray[FIRST_X], ray[FIRST_Y]);
			printf("ray[DIST_TO_WALL]=[%f]\n\n", ray[DIST_TO_WALL]);///
		}

		int c = step[FIRST_PIXEL];
		while (c < step[LAST_PIXEL])
		{
			paint_pixel(&cub->img, pixel_column, c, ORANGE);
			c++;
		}
	// }
	}
}

