#include "cub.h"

void	paint_column(t_cub *cub, int column)
{
	int	row;

	row = 0;
	while (row < cub->ray.top_wall)
	{
		paint_pixel(&cub->img, column, row, ORANGE / 4);
		row++;
	}
	while (row < cub->ray.end_wall)
	{
		if (cub->ray.side == NORTH)
			paint_pixel(&cub->img, column, row, WHITE);
		else if (cub->ray.side == SOUTH)
			paint_pixel(&cub->img, column, row, DARK_GREY);
		else if (cub->ray.side == WEST)
			paint_pixel(&cub->img, column, row, ORANGE);
		else
			paint_pixel(&cub->img, column, row, ORANGE / 2);
		row++;
	}
	while (row < WIN_HEIGHT)
	{
		paint_pixel(&cub->img, column, row, ORANGE * 2);
		row++;
	}
}
