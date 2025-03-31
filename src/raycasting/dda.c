#include "cub.h"

/*1st ligne gives a value from -1 to 1
2ng line give a value in degrees from -30 to 30 for a field of view of 60
3rd ligne corrects angle accordig to actual angle of the player*/
void	find_ray_angle(t_ray *ray, float angle, int column)
{
	ray->angle_deg = 2 * column / (float)WIN_WIDTH - 1;
	ray->angle_deg *= FIELD_OF_VIEW / 2;
	ray->angle_deg += angle;
	if (ray->angle_deg < 0)
		ray->angle_deg += 360;
	else if (ray->angle_deg >= 360)
		ray->angle_deg -= 360;
	ray->angle_rad = fabs(ray->angle_deg * (PI / 180.0));
}

void	find_offset_from_player_to_tile_edge(t_ray *ray, t_pt player_position)
{
	if (ray->angle_deg < 90)
	{
		ray->offset_to_edge.x = (ceil(player_position.x) - player_position.x);
		ray->offset_to_edge.y = (floor(player_position.y) - player_position.y);
	}
	else if (ray->angle_deg < 180)
	{
		ray->offset_to_edge.x = (ceil(player_position.x) - player_position.x);
		ray->offset_to_edge.y = (ceil(player_position.y) - player_position.y);
	}
	else if (ray->angle_deg < 270)
	{
		ray->offset_to_edge.x = (floor(player_position.x) - player_position.x);
		ray->offset_to_edge.y = (ceil(player_position.y) - player_position.y);
	}
	else
	{
		ray->offset_to_edge.x = (floor(player_position.x) - player_position.x);
		ray->offset_to_edge.y = (floor(player_position.y) - player_position.y);
	}
}

void	find_dist_first_x_and_y_intersect(t_ray *ray, t_pt player_position)
{
	ray->x = floor(player_position.x);
	ray->y = floor(player_position.y);
	if (sin(ray->angle_rad) == 0.0)
		ray->dist.x = 100;
	else
		ray->dist.x = fabs(1 / sin(ray->angle_rad));
	if (cos(ray->angle_rad) == 0.0)
		ray->dist.y = 100;
	else
		ray->dist.y = fabs(1 / cos(ray->angle_rad));
	ray->step_x = 1;
	ray->step_y = 1;
	if (ray->offset_to_edge.x < 0)
		ray->step_x = -1;
	if (ray->offset_to_edge.y < 0)
		ray->step_y = -1;
	ray->dda.x = fabs(ray->offset_to_edge.x * ray->dist.x);
	ray->dda.y = fabs(ray->offset_to_edge.y * ray->dist.y);
}

void	digital_differential_analyser(t_ray *ray, t_map *map, t_pt player_position)
{
	ray->hit_count = 0;
	while (ray->y >= 0 && ray->x >= 0
		&& ray->y <= map->height && ray->x <= map->width
		&& map->tiles[ray->y][ray->x].type != '1')
	{
		if (map->tiles[ray->y][ray->x].type != '0' && ray->hit_count < 9)
			identify_block(&ray->hit[ray->hit_count], ray, map, player_position);
		if (fabs(ray->dda.x) < fabs(ray->dda.y))
		{
			ray->side = LEFT;
			ray->x += ray->step_x;
			ray->dda.x += ray->dist.x;
		}
		else
		{
			ray->side = TOP;
			ray->y += ray->step_y;
			ray->dda.y += ray->dist.y;
		}
	}
}

/* pixel column from 0 to WIN_WIDTH */
void	raycasting(t_cub *cub)
{
	t_ray	ray;
	int		column;
	int		layer_index;

	column = 0;
	floorcasting(cub);
	while (column < WIN_WIDTH - 1)
	{
		find_ray_angle(&ray, cub->player.angle, column);
		find_offset_from_player_to_tile_edge(&ray, cub->player.grid_pt);
		find_dist_first_x_and_y_intersect(&ray, cub->player.grid_pt);
		digital_differential_analyser(&ray, cub->map, cub->player.grid_pt);
		identify_block(&ray.hit[ray.hit_count], &ray, cub->map, cub->player.grid_pt);
		debug_print(cub, column);
		layer_index = ray.hit_count - 1;
		while (layer_index >= 0)
		{
			paint_column(cub, &ray.hit[layer_index], column, layer_index == ray.hit_count - 1);
			layer_index--;
		}
		column++;
	}
}

