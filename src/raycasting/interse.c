#include "cub.h"

/*printf("edge N=[%f], S=[%f], W=[%f], E=[%f]", cub->player.edge[0],
	 cub->player.edge[1],
		cub->player.edge[2], cub->player.edge[3]);*/
void	distance_edge(t_cub *cub)
{
	cub->player.edge[0] = 1 - (cub->player.grid_pt.y - floor(cub->player.grid_pt.y));
	cub->player.edge[1] = (cub->player.grid_pt.y - floor(cub->player.grid_pt.y));
	cub->player.edge[2] = 1 - (cub->player.grid_pt.x - floor(cub->player.grid_pt.x));
	cub->player.edge[3] = (cub->player.grid_pt.x - floor(cub->player.grid_pt.x));
}

double	find_dist_to_wall(t_cub *cub, double *ray)
{
	(void)cub;
	(void)ray;
	//ray[DIST_X] = ray[ANGLE];

	// radian = angle * RADIAN;
	// cos_angle = cos(radian);
	// sin_angle = sin(radian);
	// rotated.x = cos_angle * point->x - sin_angle * point->y;
	// rotated.y = sin_angle * point->x + cos_angle * point->y;
	// point->x = rotated.x;
	// point->y = rotated.y;

	return ((double)1);
}

/*1st ligne gives a value from -1 to 1
2ng line give a value in degrees from -30 to 30 for a field of view of 60
3rd ligne corrects angle accordig to actual angle of the player*/
void	find_ray_angle(t_cub *cub, int pixel_column, double *ray)
{
	double	angle;

	angle = 2 * (pixel_column / (double)WIN_WIDTH) - 1;
	angle = angle * FIELD_OF_VIEW / 2;
	angle = angle + cub->player.player_angle;
	if (angle < 0)
		angle = angle + 360;
	ray[ANGLE_DEG] = angle;
	ray[ANGLE_RAD] = angle / (double)360;
}

/*pixel column from 0 to WIN_WIDTH*/
void	raycasting(t_cub *cub)
{
	int		pixel_column;
	double	ray[8];

	pixel_column = 0;
	while (pixel_column++ < WIN_WIDTH)
	{
		find_ray_angle(cub, pixel_column, ray);
		if (pixel_column == 1 || pixel_column == 250 || pixel_column == 499)
			printf("pixel_column=[%d] angle_deg=[%f] angle_rad=[%f]\n", pixel_column, ray[ANGLE_DEG], ray[ANGLE_RAD]);//
		ray[DIST_TO_WALL] = find_dist_to_wall(cub, ray);
		//ray[START_PAINT] = start_stop(cub, ray[DIST_TO_WALL], START_PAINT);
		//ray[STOP_PAINT] = start_stop(cub, ray[DIST_TO_WALL], STOP_PAINT);
		//paint(cub, pixel_column, ray[START_PAINT], ray[STOP_PAINT]);
	}
}
