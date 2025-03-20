/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:39 by mkling            #+#    #+#             */
/*   Updated: 2025/03/21 00:28:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_red(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_green(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_blue(int color)
{
	return (color & 0xFF);
}

int	encode_rgb(t_byte red, t_byte green, t_byte blue)
{
	return (red << 16 | green << 8 | blue);
}

int	gradientify(t_cub *cub, int color)
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;
	double	angle;

	(void)cub;
	red = get_red(color);
	green = get_green(color);
	blue = get_blue(color);

	angle = cub->ray.angle_deg;
	if (cub->ray.side == EAST || cub->ray.side == WEST)
		angle += 90;
	angle = fmod(angle, 180);
	angle -= 90;
	angle = fabs(angle);
	angle /= 90;
	red = (t_byte)(red * angle);
	green = (t_byte)(green * angle);
	blue = (t_byte)(blue * angle);
	// DO STUFF
	// if (1)
	// 	return (color);
	return (encode_rgb(red, green, blue));
}
