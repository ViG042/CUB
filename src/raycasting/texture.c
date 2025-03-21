#include "cub.h"

void	paint_column(t_cub *cub, int column)
{
	int	row;

	row = 0;
	while (row < cub->ray.top_wall)
	{
		paint_pixel(&cub->img, column, row, shade_up_down(row, BLUE));
		row++;
	}
	while (row < cub->ray.end_wall)
	{
		if (cub->ray.side == NORTH)
			paint_pixel(&cub->img, column, row, shade_left_right(cub, ORANGE));
		else if (cub->ray.side == SOUTH)
			paint_pixel(&cub->img, column, row, shade_left_right(cub, VIOLET));
		else if (cub->ray.side == WEST)
			paint_pixel(&cub->img, column, row, shade_left_right(cub, YELLOW));
		else
			paint_pixel(&cub->img, column, row, shade_left_right(cub, TEAL));
		row++;
	}
	while (row < WIN_HEIGHT)
	{
		paint_pixel(&cub->img, column, row, shade_up_down(row, GREY));
		row++;
	}
}
