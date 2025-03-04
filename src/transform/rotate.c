/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:02:27 by mkling            #+#    #+#             */
/*   Updated: 2025/03/04 19:31:29 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	multiply_2dvector(t_pt *vector, t_pt *other_vector)
{
	t_pt	result;

	result.x = vector->x * other_vector->x;
	result.y = vector->y * other_vector->y;
	vector->x = result.x;
	vector->y = result.y;
}

void	scale_2dvector(t_pt *vector, float scalar)
{
	t_pt	result;

	result.x += vector->x * scalar;
	result.y += vector->y * scalar;

	vector->x = result.x;
	vector->y = result.y;
	fprintf(stderr, "vetor x is %f, vector y is %f\n", vector->x, vector->y);
}

void	rotate_point(t_pt *point, t_pt *center, float angle)
{
	float	radian;
	float	cos_angle;
	float	sin_angle;
	t_pt	new;

	radian = angle * RADIAN;
	cos_angle = cos(radian);
	sin_angle = sin(radian);
	new.x = cos_angle * (point->x - center->x)
		- sin_angle * (point->y - center->y) + center->x;
	new.y = sin_angle * (point->x - center->x)
		+ cos_angle * (point->y - center->y) + center->y;
	point->x = new.x;
	point->y = new.y;
}
