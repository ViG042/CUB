/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:07:58 by mkling            #+#    #+#             */
/*   Updated: 2025/03/03 15:22:32 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

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
			put_pixel(img, column++, row, color);
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

// void	paint_minimap(t_cub *cub, t_map *map)
// {
// 	int		index;

// 	index = 0;
// 	while (index < map->total)
// 	{
// 		if (index % map->width != 0)
// 		{
// 			paint_line(map->array[index - 1], map->array[index], cub);
// 		}
// 		if (index >= map->width)
// 		{
// 			paint_line(map->array[index - map->width], map->array[index], cub);
// 		}
// 		index++;
// 	}
// }

int	render(t_cub *cub)
{
	if (cub->win == NULL)
		return (1);
	paint_background(&cub->img, BLACK);
	// paint_minimap(cub->map, cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.mlx_img, 0, 0);
	return (0);
}
