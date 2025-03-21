#include "cub.h"

void	calculate_dist_to_wall(t_cub *cub)
{
	if (cub->ray.side == NORTH || cub->ray.side == SOUTH)
		cub->ray.wall_dist = fabs(fabs(cub->ray.dda_y) - fabs(cub->ray.dist_y));
	else
		cub->ray.wall_dist = fabs(fabs(cub->ray.dda_x) - fabs(cub->ray.dist_x));
}

// void	calculate_dist_in_texture(t_cub *cub)
// {
// 	double	dist;

// 	if (cub->ray.side == NORTH || cub->ray.side == SOUTH)
// 	{
// 		dist = sqrt(pow(cub->ray.dda_x, 2) - pow(cub->ray.wall_dist, 2));
// 		if (cub->ray.angle_deg < 180)
// 			dist += cub->player.grid_pt.x;
// 		else
// 			dist = cub->player.grid_pt.x - dist;
// 	}
// 	else
// 	{
// 		dist = sqrt(pow(cub->ray.dda_y, 2) - pow(cub->ray.wall_dist, 2));
// 		if (cub->ray.angle_deg > 90 && cub->ray.angle_deg < 270)
// 			dist += cub->player.grid_pt.y;
// 		else
// 			dist = cub->player.grid_pt.y - dist;
// 	}
// 	cub->ray.dist_in_text = dist;
// 	cub->ray.dist_in_text = dist - (int)dist;
// 	if ((cub->ray.side == EAST && cub->ray.angle_deg < 90)
// 		|| (cub->ray.side == SOUTH && cub->ray.angle_deg < 180)
// 		|| (cub->ray.side == WEST && cub->ray.angle_deg < 270)
// 		|| (cub->ray.side == NORTH && cub->ray.angle_deg > 270))
// 		cub->ray.dist_in_text = 1 - cub->ray.dist_in_text;
// }

void	calculate_dist_in_texture(t_cub *cub, int pixel_column)
{
	double	d;

	if (cub->ray.side == NORTH || cub->ray.side == SOUTH)
	{
		if (pixel_column == WIN_WIDTH / 2)
		{
		printf("NORTH or SOUTH\n");
		printf("cub->player.grid_pt.x=[%f]\n", cub->player.grid_pt.x);
		printf("cub->ray.wall_dist=[%f]\n", cub->ray.wall_dist);
		printf("cub->ray.angle_rad=[%f]\n", cub->ray.angle_rad);
		printf("sin(cub->ray.angle_rad)=[%f]\n", sin(cub->ray.angle_rad));
		}
		d = cub->player.grid_pt.x + cub->ray.wall_dist * sin(cub->ray.angle_rad);
	}
	else
	{
		if (pixel_column == WIN_WIDTH / 2)
		{
		printf("AST or WEST\n");
		printf("cub->player.grid_pt.y=[%f]\n", cub->player.grid_pt.y);
		printf("cub->ray.wall_dist=[%f]\n", cub->ray.wall_dist);
		printf("cub->ray.angle_rad=[%f]\n", cub->ray.angle_rad);
		printf("cos(cub->ray.angle_rad)=[%f]\n", cos(cub->ray.angle_rad));
		}
		d = cub->player.grid_pt.y - cub->ray.wall_dist * cos(cub->ray.angle_rad);
	}
	cub->ray.dist_in_text = d;// - (int)d;
	if (pixel_column == WIN_WIDTH / 2)
		printf("dist in text=[%f]\n", cub->ray.dist_in_text);
	cub->ray.dist_in_text = d- (int)d;
	if (pixel_column == WIN_WIDTH / 2)
		printf("floor dist in text=[%f]\n", cub->ray.dist_in_text);
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
