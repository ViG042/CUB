/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:56:50 by mkling            #+#    #+#             */
/*   Updated: 2025/04/02 11:57:25 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	fclamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	shade_left_right(t_hit *block, int color)
{
	float	angle;
	float	distance;

	angle = block->angle;
	if (block->side == EAST || block->side == WEST)
		angle += 90;
	angle = fmod(angle, 180);
	angle -= 90;
	angle = fabs(angle);
	angle /= 90;
	angle = angle / 2 + 0.5;
	distance = 1 / block->distance;
	if (distance > 1)
		distance = 1;
	return (blend(BLACK, blend(BLACK, color, distance), angle));
}

int	shade_up_down(int row, int color)
{
	float	distance;

	distance = row - WIN_HEIGHT / 2;
	distance /= WIN_HEIGHT / 2;
	distance = fabs(distance + 0.1);
	return (blend(BLACK, color, distance));
}
