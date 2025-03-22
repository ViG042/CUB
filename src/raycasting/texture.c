#include "cub.h"

void	paint_pixel_3(t_cub *cub, int column, int row, int type)
{
	int	color;
	int	img_x;
	int	img_y;

	img_x = (int)(cub->ray.dist_in_text * (float)cub->elem[type].width);
	if (cub->ray.wall_dist < 1)
		img_y = ((float)(row - cub->ray.top_wall)
				/ (float)cub->ray.wall_height * (float)cub->elem[type].height)
			+ (float)cub->elem[type].height / 2.0 * (1.0 - cub->ray.wall_dist);
	else
		img_y = ((float)(row - cub->ray.top_wall)
				/ (float)cub->ray.wall_height * (float)cub->elem[type].width);
	color = read_pixel(&cub->elem[type].texture, img_x, img_y);
	paint_pixel(&cub->visual, column, row, color);
}

void	paint_pixel_2(t_cub *cub, int column, int row, int type)
{
	if (cub->elem[type].texture.mlx_img)
	{
		paint_pixel_3(cub, column, row, type);
	}
	else if (cub->elem[type].color)
	{
		paint_pixel(&cub->visual, column, row,
			shade_left_right(cub, cub->elem[type].color));
	}
	else
		paint_pixel(&cub->visual, column, row, cub->elem[type].back_up);
}

void	paint_wall_column(t_cub *cub, int column, int row)
{
	if (cub->map->clean_map[cub->ray.y][cub->ray.x] == 'D')
		paint_pixel_2(cub, column, row, D);
	else if (cub->ray.side == NORTH)
		paint_pixel_2(cub, column, row, NO);
	else if (cub->ray.side == SOUTH)
		paint_pixel_2(cub, column, row, SO);
	else if (cub->ray.side == WEST)
		paint_pixel_2(cub, column, row, WE);
	else
		paint_pixel_2(cub, column, row, EA);
}

void	paint_column(t_cub *cub, int column)
{
	int	row;
	int	color;

	row = 0;
	while (row < cub->ray.top_wall)
	{
		if (cub->elem[F].color)
			color = shade_up_down(row, cub->elem[F].color);
		else
			color = cub->elem[F].back_up;
		paint_pixel(&cub->visual, column, row++, color);
	}
	while (row < cub->ray.end_wall)
		paint_wall_column(cub, column, row++);
	while (row < WIN_HEIGHT)
	{
		if (cub->elem[C].color)
			color = shade_up_down(row, cub->elem[C].color);
		else
			color = cub->elem[C].back_up;
		paint_pixel(&cub->visual, column, row++, color);
	}
}
