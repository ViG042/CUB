#include "cub.h"

void	paint_column(t_cub *cub, int column)
{
	int	row;

	row = 0;
	while (row < cub->ray.top_wall)
	{
		paint_pixel(&cub->img, column, row, grad_floor_ceil(cub, row, BLUE));
		row++;
	}
	while (row < cub->ray.end_wall)
	{
		if (cub->ray.side == NORTH)
			paint_pixel(&cub->img, column, row, gradientify_wall(cub, ORANGE));
		else if (cub->ray.side == SOUTH)
			paint_pixel(&cub->img, column, row, gradientify_wall(cub, VIOLET));
		else if (cub->ray.side == WEST)
			paint_pixel(&cub->img, column, row, gradientify_wall(cub, YELLOW));
		else
			paint_pixel(&cub->img, column, row, gradientify_wall(cub, TEAL));
		row++;
	}
	while (row < WIN_HEIGHT)
	{
		paint_pixel(&cub->img, column, row, grad_floor_ceil(cub, row, GREY));
		row++;
	}
}
