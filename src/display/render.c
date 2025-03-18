/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:07:58 by mkling            #+#    #+#             */
/*   Updated: 2025/03/18 14:07:09 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_in_window(int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x > WIN_WIDTH || y > WIN_HEIGHT)
		return (0);
	return (1);
}

void	paint_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (!is_in_window(x, y))
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

void	put_point(t_cub *cub, t_pt point)
{
	char	*pixel;
	int		i;

	if (point.x < 0 || point.y < 0
		|| point.x > WIN_WIDTH || point.y > WIN_HEIGHT)
		return ;
	i = cub->img.bit_per_pixel - 8;
	pixel = cub->img.address + ((int)point.y * cub->img.line_len
			+ (int)point.x * (cub->img.bit_per_pixel / 8));
	while (i >= 0)
	{
		if (cub->img.endian != 0)
			*pixel++ = (point.rgb >> i) & 0xFF;
		else
			*pixel++ = (point.rgb >> (cub->img.bit_per_pixel
						- 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	render(t_cub *cub)
{
	char	*itoa_fps;

	if (cub->win == NULL)
		return (1);


	paint_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.mlx_img, 0, 0);
	itoa_fps = ft_itoa(cub->display.fps);
	mlx_string_put(cub->mlx, cub->win, 5, WIN_HEIGHT - 5, WHITE, itoa_fps);
	free(itoa_fps);
	return (0);
}
