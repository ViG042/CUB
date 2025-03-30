#include "cub.h"

void	paint_texture_to_wall(t_img *img, t_hit *block, t_elem *texture, t_pix *pixel)
{
	int	color;
	int	img_x;
	int	img_y;

	img_x = (int)(block->texture_offset * texture->width);
	if (block->distance < 1)
		img_y = ((float)(pixel->row - block->top_pixel)
				/ (float)block->height * (float)texture->height)
			+ (float)texture->height / 2.0 * (1.0 - block->distance);
	else
		img_y = ((float)(pixel->row - block->top_pixel)
				/ (float)block->height * (float)texture->width);
	color = read_pixel(&texture->texture, img_x, img_y);
	paint_pixel(img, pixel->column, pixel->row, color);
}

void	paint_block(t_cub *cub, t_hit *block, int column, int row)
{
	t_pix	pixel;

	pixel.row = row;
	pixel.column = column;
	if (block->type != WALL)
	{
		if (cub->elem[block->type].texture.mlx_img)
			paint_texture_to_wall(&cub->visual, block, &cub->elem[block->type], &pixel);
		else
			paint_pixel(&cub->visual, column, row, cub->elem[block->type].color);
	}
	else
	{
		if (cub->elem[block->side].texture.mlx_img)
			paint_texture_to_wall(&cub->visual, block, &cub->elem[block->side], &pixel);
		else
			paint_pixel(&cub->visual, column, row, cub->elem[block->side].color);
	}
}

void	paint_column(t_cub *cub, t_hit *block, int column, int is_last_block)
{
	int	row;
	int	color;

	row = 0;
	while (is_last_block && row < block->top_pixel)
	{
		color = shade_up_down(row, cub->elem[F].color);
		paint_pixel(&cub->visual, column, row++, color);
	}
	row = block->top_pixel;
	while (row < block->end_pixel)
		paint_block(cub, block, column, row++);
	while (is_last_block && row < WIN_HEIGHT)
	{
		color = shade_up_down(row, cub->elem[C].color);
		paint_pixel(&cub->visual, column, row++, color);
	}
}
