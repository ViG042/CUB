#include "cub.h"

void	calculate_dist_to_wall(t_cub *cub)
{
	if (cub->ray.side == NORTH || cub->ray.side == SOUTH)
		cub->ray.wall_dist = fabs(fabs(cub->ray.dda_y) - fabs(cub->ray.dist_y));
	else
		cub->ray.wall_dist = fabs(fabs(cub->ray.dda_x) - fabs(cub->ray.dist_x));
}

void	calculate_dist_in_texture(t_cub *cub)
{
	float	d;

	if (cub->ray.side == NORTH || cub->ray.side == SOUTH)
		d = cub->player.grid_pt.x
			+ cub->ray.wall_dist * sin(cub->ray.angle_rad);
	else
		d = cub->player.grid_pt.y
			- cub->ray.wall_dist * cos(cub->ray.angle_rad);
	cub->ray.dist_in_text = d - (int)d;
	if (cub->ray.side == WEST || cub->ray.side == SOUTH)
		cub->ray.dist_in_text = 1 - cub->ray.dist_in_text;
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
