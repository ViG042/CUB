#include "cub.h"

int	get_color_from_elem(t_hit *block, t_elem *elem, t_pix *pixel)
{
	t_pix	texture_pix;

	texture_pix.x = (int)(block->texture_offset * elem->width);
	if (block->distance < 1)
		texture_pix.y = ((float)(pixel->y - block->top_pixel)
			/ (float)block->height * (float)elem->height)
			+ (float)elem->height / 2.0 * (1.0 - block->distance);
	else
		texture_pix.y = ((float)(pixel->y - block->top_pixel)
				/ (float)block->height * (float)elem->width);
	if (block->type == D)
		texture_pix.y -= elem->height * block->tile->state;
	if (elem->texture.mlx_img)
		return (read_pixel(&elem->texture, elem->width,
			elem->height, texture_pix.x, texture_pix.y));
	if (texture_pix.y < 0 || texture_pix.y > elem->height)
		return (TRANSPARENT);
	else
		return (elem->color);
}

void	paint_block(t_cub *cub, t_hit *block, int column, int row)
{
	t_elem	elem;
	t_pix	pixel;
	int		color;

	pixel.y = row;
	pixel.x = column;
	if (block->type != WALL)
		elem = cub->elem[block->type];
	else
		elem = cub->elem[block->side];
	color = get_color_from_elem(block, &elem, &pixel);
	paint_pixel(&cub->visual, column, row, shade_left_right(block, color));
}

void	paint_column(t_cub *cub, t_hit *block, int column, int /*is_last_block*/)
{
	int	row;
	// int	color;

	row = 0;
	// while (is_last_block && row < block->top_pixel)
	// {
	// 	color = shade_up_down(row, cub->elem[C].color);
	// 	paint_pixel(&cub->visual, column, row++, color);
	// }
	row = block->top_pixel;
	while (row < block->end_pixel)
		paint_block(cub, block, column, row++);
	// while (is_last_block && row < WIN_HEIGHT)
	// {
	// 	color = shade_up_down(row, cub->elem[F].color);
	// 	paint_pixel(&cub->visual, column, row++, color);
	// }
}
