/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:56:25 by mkling            #+#    #+#             */
/*   Updated: 2025/04/02 12:42:24 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_color	split_rgb(int rgb)
{
	t_color	c;

	c.red = get_red(rgb);
	c.green = get_green(rgb);
	c.blue = get_blue(rgb);
	return (c);
}

int	merge_rgb(t_color rgb)
{
	return (encode_rgb(rgb.red, rgb.green, rgb.blue));
}

/* To avoid rgb overflow */
t_byte	mix_color(t_byte color1, t_byte color2, float ratio)
{
	int		integer;
	t_byte	result;

	integer = color1 * (1 - ratio) + color2 * ratio;
	if (integer >= 255)
		result = 255;
	else if (integer <= 0)
		result = 0;
	else
		result = (t_byte)integer;
	return (result);
}

int	blend(int color1, int color2, float ratio)
{
	t_color	c1;
	t_color	c2;
	t_color	mix;
	int		result;

	if (color1 == TRANSPARENT)
		return (color2);
	if (color2 == TRANSPARENT)
		return (color1);
	c1 = split_rgb(color1);
	c2 = split_rgb(color2);
	mix.red = mix_color(c1.red, c2.red, ratio);
	mix.green = mix_color(c1.green, c2.green, ratio);
	mix.blue = mix_color(c1.blue, c2.blue, ratio);
	result = merge_rgb(mix);
	if (result == TRANSPARENT)
		result += 1;
	return (result);
}

void	paint_pixel_blend(t_img *img, int x, int y, int color)
{
	int		prev_color;
	t_pix	pixel;

	if (!is_in_window(x, y))
		return ;
	pixel.x = x;
	pixel.y = y;
	prev_color = read_pixel(img, WIN_WIDTH, WIN_HEIGHT, pixel);
	paint_pixel(img, x, y, blend(prev_color, color, 0.7));
}
