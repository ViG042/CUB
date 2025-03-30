#include "cub.h"

void	set_block_type(t_hit *block, char map_char)
{
	if (map_char == 'D')
		block->type = DOOR;
	// else if (map_char == 'G')
	// 	block->type = GOLEM;
	else
		block->type = WALL;
}

void	set_dist_to_block(t_hit *block, t_ray *ray)
{
	if (block->side == NORTH || block->side == SOUTH)
		block->distance = fabs(fabs(ray->dda.y) - fabs(ray->dist.y));
	else
		block->distance = fabs(fabs(ray->dda.x) - fabs(ray->dist.x));
}

void	set_texture_offset(t_hit *block, t_ray *ray, t_pt player_position)
{
	float	offset;

	if (block->side == NORTH || block->side == SOUTH)
		offset = player_position.x + block->distance * sin(ray->angle_rad);
	else
		offset = player_position.y - block->distance * cos(ray->angle_rad);
	block->texture_offset = offset - (int)offset;
	if (block->side == WEST || block->side == SOUTH)
		block->texture_offset = 1 - block->texture_offset;
}

void	set_block_height_top_end_pixels(t_hit *block)
{
	block->height = (int)(WIN_HEIGHT / block->distance);
	block->top_pixel = (WIN_HEIGHT - block->height) / 2;
	if (block->top_pixel < 0)
		block->top_pixel = 0;
	block->end_pixel = block->top_pixel + block->height;
	if (block->end_pixel >= WIN_HEIGHT)
		block->end_pixel = WIN_HEIGHT;
}

void	identify_block(t_hit *block, t_ray *ray, t_map *map, t_pt player_position)
{
	define_collision_side(block, ray);
	set_block_type(block, map->clean_map[ray->y][ray->x]);
	set_dist_to_block(block, ray);
	set_block_height_top_end_pixels(block);
	set_texture_offset(block, ray, player_position);
	ray->hit_count++;
}
