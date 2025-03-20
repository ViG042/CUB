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

	angle = 2 * pixel_column / (double)WIN_WIDTH - 1;
	angle = angle * FIELD_OF_VIEW / 2;
	angle = angle + cub->player.player_angle;
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	ray[ANGLE_DEG] = angle;
	ray[ANGLE_RAD] = fabs(angle * (PI / 180.0));

	if (sin(ray[ANGLE_RAD]) == 0.0)
		ray[DIST_X] = 100;
	else
		ray[DIST_X] = fabs(1 / sin(ray[ANGLE_RAD]));
	if (cos(ray[ANGLE_RAD]) == 0.0)
		ray[DIST_Y] = 100;
	else
		ray[DIST_Y] = fabs(1 / cos(ray[ANGLE_RAD]));

	init_first_dist(cub, ray);
	// if (ray[FIRST_X] < 0)
	// 	ray[DIST_X] *= -1;
	// if (ray[FIRST_Y] < 0)
	// 	ray[DIST_Y] *= -1;
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
void	digital_differential_analyser(t_cub *cub, double *ray, int *step)
{
	ray[DDA_X] = fabs(ray[FIRST_X]);
	ray[DDA_Y] = fabs(ray[FIRST_Y]);
	while (cub->map->clean_map[step[Y]][step[X]] == '0')
	{
		if (fabs(ray[DDA_X]) < fabs(ray[DDA_Y]))
		{
			step[LAST_MOVE] = LEFT;
			step[X] += step[STEP_X];
			ray[DDA_X] += ray[DIST_X];
		}
		else
		{
			step[LAST_MOVE] = TOP;
			step[Y] += step[STEP_Y];
			ray[DDA_Y] += ray[DIST_Y];
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

void	calculate_dist_to_wall(double *ray, int *step)
{
	if (step[LAST_MOVE] == NORTH || step[LAST_MOVE] == SOUTH)
		ray[DIST_TO_WALL] = fabs(fabs(ray[DDA_Y]) - fabs(ray[DIST_Y]));
	else
		ray[DIST_TO_WALL] = fabs(fabs(ray[DDA_X]) - fabs(ray[DIST_X]));
}

void	calculate_wall_height(double *ray, int *step)
{

	step[HEIGHT] = (int)(WIN_HEIGHT / ray[DIST_TO_WALL]);
	//(int)(((max - ray[DIST_TO_WALL]) / max) * WIN_HEIGHT);

	step[FIRST_PIXEL] = (WIN_HEIGHT - step[HEIGHT]) / 2;
	if (step[FIRST_PIXEL] < 0)
		step[FIRST_PIXEL] = 0;
	step[LAST_PIXEL] = step[FIRST_PIXEL] + step[HEIGHT];
	if (step[LAST_PIXEL] >= WIN_HEIGHT)
		step[LAST_PIXEL] = WIN_HEIGHT;


		  //calculate lowest and highest pixel to fill in current stripe
		//   int drawStart = -lineHeight / 2 + h / 2;
		//   if(drawStart < 0)drawStart = 0;
		//   int drawEnd = lineHeight / 2 + h / 2;
		//   if(drawEnd >= h)drawEnd = h - 1;
}

void	begug_print(double *ray, int *step, int pixel_column)
{
	if (pixel_column == 2 ||
		pixel_column == WIN_WIDTH / 2 ||
		pixel_column == WIN_WIDTH - 2)
	{
		printf("\n\npixel column is %d\n", pixel_column);
		printf("wall hit at X=[%d] Y=[%d]\n", step[X], step[Y]);
		printf("LAST_MOVE=[%d]\n", step[LAST_MOVE]);
		printf("ray[DIST_TO_WALL]=[%f]\n\n", ray[DIST_TO_WALL]);
		printf("pixel_column=[%d] angle_deg=[%f] angle_rad=[%f] \
			composante_x=[%f] composante_y=[%f] first_x[%f] first_y=[%f] \
			X=[%d] Y=[%d] STEP_X=[%d] STEP_Y=[%d]\n",
			pixel_column, ray[ANGLE_DEG], ray[ANGLE_RAD],
			ray[DIST_X], ray[DIST_Y], ray[FIRST_X], ray[FIRST_Y],
			step[X], step[Y], step[STEP_X], step[STEP_Y]);
	}
}

void paint_column(t_cub *cub, int *step, int pixel_column)
{
	int c;

	c = 0;
	while (c < step[FIRST_PIXEL])
	{
		paint_pixel(&cub->img, pixel_column, c, ORANGE / 4);
		c++;
	}
	while (c < step[LAST_PIXEL])
	{
		if (step[LAST_MOVE] == NORTH)
			paint_pixel(&cub->img, pixel_column, c, WHITE);
		else if (step[LAST_MOVE] == SOUTH)
			paint_pixel(&cub->img, pixel_column, c, DARK_GREY);
		else if (step[LAST_MOVE] == WEST)
			paint_pixel(&cub->img, pixel_column, c, ORANGE);
		else
			paint_pixel(&cub->img, pixel_column, c, ORANGE / 2);
		c++;
	}
	while (c < WIN_HEIGHT)
	{
		paint_pixel(&cub->img, pixel_column, c, ORANGE * 2);
		c++;
	}
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
		init_ray(cub, pixel_column, ray);
		init_step(cub, ray, step);
		digital_differential_analyser(cub, ray, step);
		define_surface_collision(ray, step);
		calculate_dist_to_wall(ray, step);
		calculate_wall_height(ray, step);
		//begug_print(ray, step, pixel_column);
		paint_column(cub, step, pixel_column);
	}
}

