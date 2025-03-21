#include "cub.h"

void	paint_pixel_3(t_cub *cub, int column, int row, int type)
{
	int	color;
	int	img_x;
	int	img_y;

	img_x = (int)(cub->ray.dist_in_text * (double)cub->w);
	img_y = (int)((double)(row - cub->ray.top_wall) / (double)cub->ray.wall_height * (double)cub->h);
	color = read_pixel(&cub->elem[type].texture, img_x, img_y);
	if (column == WIN_HEIGHT / 2)
	{
		printf("type is %d and texture=[%s]\n", type, cub->elem[type].description);
		printf("dist_in_text=[%f] img_x=[%d]  w=[%d]\n", cub->ray.dist_in_text, img_x, cub->w);
		printf("row=[%f] cub->ray.wall_height=[%f]\n", (double)row, (double)cub->ray.wall_height);
		printf("row/cub->ray.wall_height=[%f] img_y=[%d]  h=[%d]\n\n", (double)row / (double)cub->ray.wall_height, img_y, cub->h);
		printf("color is %x\n", color);
	}
	paint_pixel(&cub->img, column, row, color);
}

void	paint_pixel_2(t_cub *cub, int column, int row, int type)
{
	if (cub->elem[type].texture.mlx_img)
	{
		paint_pixel_3(cub, column, row, type);
	}
	else if (cub->elem[type].color)
	{
		paint_pixel(&cub->img, column, row,
			gradientify_wall(cub, cub->elem[type].color));
	}
	else
		paint_pixel(&cub->img, column, row, cub->elem[type].back_up);
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
	color = 42;

	// if (column == WIN_HEIGHT / 2 + 1)
	// {
	// 	//printf("type is %d and texture=[%s]\n", type, cub->elem[type].description);
	// 	//printf("dist_in_text=[%f] img_x=[%d]  w=[%d]\n", cub->ray.dist_in_text, img_x, cub->w);
	// 	printf("coucou row=[%f] cub->ray.wall_height=[%f]\n", (double)row, (double)cub->ray.wall_height);
	// 	//printf("coucou row/cub->ray.wall_height=[%f] img_y=[%d]  h=[%d]\n\n", (double)row / (double)cub->ray.wall_height, img_y, cub->h);
	// 	printf("cpicpi color is %x\n", color);
	// }
	while (row < cub->ray.top_wall)
	{
		if (cub->elem[F].color)
			color = grad_floor_ceil(cub, row, cub->elem[F].color);
		else
			color = cub->elem[F].back_up;
		paint_pixel(&cub->img, column, row, color);
		row++;
	}
	while (row < cub->ray.end_wall)
	{

	// if (column == WIN_WIDTH / 2)
	// {
	// 	//printf("type is %d and texture=[%s]\n", type, cub->elem[type].description);
	// 	//printf("dist_in_text=[%f] img_x=[%d]  w=[%d]\n", cub->ray.dist_in_text, img_x, cub->w);
	// 	//printf("coucou row=[%f] cub->ray.wall_height=[%f]\n", (double)row, (double)cub->ray.wall_height);
	// 	//printf("coucou row/cub->ray.wall_height=[%f] img_y=[%d]  h=[%d]\n\n", (double)row / (double)cub->ray.wall_height, img_y, cub->h);
	// 	//printf("cpicpi color is %x\n", color);
	// 	printf("test apres %f\n", cub->ray.dist_in_text);
	// }
		paint_wall_column(cub, column, row);
		row++;
	}
	while (row < WIN_HEIGHT)
	{
		if (cub->elem[C].color)
			color = grad_floor_ceil(cub, row, cub->elem[C].color);
		else
			color = cub->elem[C].back_up;
		paint_pixel(&cub->img, column, row, color);
		row++;
	}
}
