/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:02:27 by mkling            #+#    #+#             */
/*   Updated: 2025/03/12 16:35:37 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pt	normalize_vector(t_pt *point)
{
	t_pt	unit_vector;
	double	magnitude;

	unit_vector = *point;
	magnitude = sqrt(point->x * point->x + point->y * point->y);
	if (magnitude != 0)
		unit_vector.x /= magnitude;
	if (point->y != 0)
		unit_vector.y /= magnitude;
	return (unit_vector);
}

void	rotate_point(t_cub *cub, t_pt *point, t_pt *center, double angle)
{
	double	radian;
	double	cos_angle;
	double	sin_angle;
	t_pt	centered;
	t_pt	rotated;

	(void)cub;
	centered.x = point->x - center->x;
	centered.y = point->y - center->y;
	radian = angle * RADIAN;
	cos_angle = cos(radian);
	sin_angle = sin(radian);
	rotated.x = cos_angle * centered.x - sin_angle * centered.y;
	rotated.y = sin_angle * centered.x + cos_angle * centered.y;
	point->x = rotated.x + center->x;
	point->y = rotated.y + center->y;
}
