/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/04/02 12:20:15 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rotate_point(t_pt *point, t_pt *center, float angle)
{
	float	radian;
	float	cos_angle;
	float	sin_angle;
	t_pt	centered;
	t_pt	rotated;

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

t_pt	scale_point(t_pt pt, int scale)
{
	t_pt	projection;

	projection.x = pt.x * scale;
	projection.y = pt.y * scale;
	return (projection);
}
