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

/*1st ligne gives a value from -1 to 1
2ng line give a value in degrees from -30 to 30 for a field of view of 60
3rd ligne corrects angle accordig to actual angle of the player*/
double	find_ray_angle(t_cub *cub, int pixel_column)
{
	double	angle;

	angle = 2 * (pixel_column / WIN_WIDTH) - 1;
	angle = angle * FIELD_OF_VIEW / 2;
	angle = angle + cub->player.player_angle;
	return (angle);
}

/*pixel column from 0 to WIN_WIDTH*/
void	raycasting(t_cub *cub)
{
	int		pixel_column;
	double	ray[4];

	pixel_column = 0;
	while (pixel_column++ < WIN_WIDTH)
	{
		ray[ANGLE] = find_ray_angle(cub, pixel_column);
		ray[DIST_TO_WALL] = find_dist_to_wall(cub, ray[ANGLE]);
		ray[START_PAINT] = start_stop(cub, ray[DIST_TO_WALL], START_PAINT);
		ray[STOP_PAINT] = start_stop(cub, ray[DIST_TO_WALL], STOP_PAINT);
		paint(cub, pixel_column, ray[START_PAINT], ray[STOP_PAINT]);
	}
}
