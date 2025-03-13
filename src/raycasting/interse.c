#include "cub.h"

void	find_first_dist_to_wall(t_cub *cub, double *ray)
{
	double	x;
	double	y;

	x = cub->player.grid_pt.x;
	y = cub->player.grid_pt.y;
	if (ray[ANGLE_DEG] < 90)
	{
		ray[FIRST_X] = (ceil(x) - x);// ray[DIST_X];
		ray[FIRST_Y] = (floor(y) - y);// ray[DIST_Y];
	}
	else if (ray[ANGLE_DEG] < 180)
	{
		ray[FIRST_X] = (ceil(x) - x);// ray[DIST_X];
		ray[FIRST_Y] = (ceil(y) - y);// ray[DIST_Y];
	}
	else if (ray[ANGLE_DEG] < 270)
	{
		ray[FIRST_X] = (floor(x) - x);// ray[DIST_X];
		ray[FIRST_Y] = (ceil(y) - y);// ray[DIST_Y];
	}
	else
	{
		ray[FIRST_X] = (floor(x) - x);// ray[DIST_X];
		ray[FIRST_Y] = (floor(y) - y);// ray[DIST_Y];
	}
}

/*1st ligne gives a value from -1 to 1
2ng line give a value in degrees from -30 to 30 for a field of view of 60
3rd ligne corrects angle accordig to actual angle of the player*/
void	find_ray_angle_and_dist_between_lines(t_cub *cub, int pixel_column, double *ray)
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
	ray[DIST_X] = fabs(1 / cos(ray[ANGLE_RAD]));
	ray[DIST_Y] = fabs(1 / sin(ray[ANGLE_RAD]));
}

/*pixel column from 0 to WIN_WIDTH*/
void	raycasting(t_cub *cub)
{
	int		pixel_column;
	double	ray[9];

	pixel_column = 0;
	while (pixel_column++ < WIN_WIDTH)
	{
		find_ray_angle_and_dist_between_lines(cub, pixel_column, ray);
		find_first_dist_to_wall(cub, ray);

		if (pixel_column == 1 || pixel_column == 250 || pixel_column == 499)
			printf("pixel_column=[%d] angle_deg=[%f] angle_rad=[%f] \
				composante_x=[%f] composante_y=[%f] first_x[%f] first_y=[%f]\n\n",
				pixel_column, ray[ANGLE_DEG], ray[ANGLE_RAD],
				ray[DIST_X], ray[DIST_Y], ray[FIRST_X], ray[FIRST_Y]);//
		//ray[START_PAINT] = start_stop(cub, ray[DIST_TO_WALL], START_PAINT);
		//ray[STOP_PAINT] = start_stop(cub, ray[DIST_TO_WALL], STOP_PAINT);
		//paint(cub, pixel_column, ray[START_PAINT], ray[STOP_PAINT]);
	}
}
