#include "cub.h"

void	paint_column_to_buffer(t_cub *cub, int column, int row, int type)
{

}

void	buffer_non_wall(t_cub *cub)
{
	int	row;

	define_collision_side(cub);
	calculate_dist_to_wall(cub);
	calculate_wall_height(cub);
	calculate_dist_in_texture(cub);
	// debug_print(cub, column);
	row = cub->ray.top_wall;
	while (row < cub->ray.end_wall)
		paint_column_to_buffer(cub, cub->ray.column, row++, cub->ray.side);
}
