#include "cub.h"

int	get_color_from_texture(t_hit *block, t_elem *texture, t_pix *pixel)
{
	int		color;
	t_pix	texture_pixel;

	texture_pixel.x = (int)(block->texture_offset * texture->width);
	if (block->distance < 1)
		texture_pixel.y = ((float)(pixel->x - block->top_pixel)
				/ (float)block->height * (float)texture->height)
			+ (float)texture->height / 2.0 * (1.0 - block->distance);
	else
		texture_pixel.y = ((float)(pixel->x - block->top_pixel)
				/ (float)block->height * (float)texture->width);
	color = read_pixel(&texture->texture, texture_pixel.x, texture_pixel.y);
	return (color);
}

void	paint_block(t_cub *cub, t_hit *block, int column, int row)
{
	t_pix	pixel;
	int		color;

	pixel.x = row;
	pixel.y = column;
	if (block->type != WALL)
	{
		if (cub->elem[block->type].texture.mlx_img)
			color = get_color_from_texture(block, &cub->elem[block->type], &pixel);
		else
			color = cub->elem[block->type].color;
	}
	else
	{
		if (cub->elem[block->side].texture.mlx_img)
			color = get_color_from_texture(block, &cub->elem[block->side], &pixel);
		else
			color = cub->elem[block->side].color;
	}
	paint_pixel(&cub->visual, column, row, color);
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
