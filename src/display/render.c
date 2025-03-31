/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:07:58 by mkling            #+#    #+#             */
/*   Updated: 2025/03/31 08:34:08 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_transparent(int color)
{
	return (color == TRANSPARENT);
}

void	paint_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (!is_in_window(x, y) || is_transparent(color))
		return ;
	i = img->bit_per_pixel - 8;
	pixel = img->address + (y * img->line_len + x
			* (img->bit_per_pixel / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bit_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	read_pixel(t_img *img, int img_width, int img_height, int x, int y)
{
	char	*pixel;
	int		color;
	int		i;

	if (x < 0 || y < 0 || x > img_width || y > img_height)
		return (TRANSPARENT);
	color = 0;
	pixel = img->address + (y * img->line_len + x * (img->bit_per_pixel / 8));
	i = 0;
	while (i < img->bit_per_pixel)
	{
		if (img->endian != 0)
			color |= (unsigned char)(*pixel++) << (img->bit_per_pixel - 8 - i);
		else
			color |= (unsigned char)(*pixel++) << i;
		i += 8;
	}
	return (color);
}

void	paint_background(t_img *img, int color)
{
	int	row;
	int	column;

	row = 0;
	while (row < WIN_HEIGHT)
	{
		column = 0;
		while (column < WIN_WIDTH)
			paint_pixel(img, column++, row, color);
		++row;
	}
}

int	render(t_cub *cub)
{
	char	*itoa_fps;

	if (cub->win == NULL)
		return (1);
	update_player_cursor(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->visual.mlx_img, 0, 0);
	itoa_fps = ft_itoa(cub->display.fps);
	mlx_string_put(cub->mlx, cub->win, 5, WIN_HEIGHT - 5, WHITE, itoa_fps);
	free(itoa_fps);
	return (0);
}
