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
	if (cub->ray.side == NORTH || cub->ray.side == SOUTH)
	{
		cub->ray.dist_in_text = sqrt(pow(cub->ray.dda_y, 2) - pow(cub->ray.wall_dist, 2));
	}
	else
	{
		cub->ray.dist_in_text = sqrt(pow(cub->ray.dda_x, 2) - pow(cub->ray.wall_dist, 2));
	}
	//cub->ray.dist_in_text = cub->ray.dist_in_text
	//	- (int)(cub->ray.dist_in_text);
	// -/+ la first_x / first_y du player ?
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
