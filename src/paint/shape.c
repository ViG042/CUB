/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:24:02 by mkling            #+#    #+#             */
/*   Updated: 2025/03/21 01:49:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	paint_square(t_img *img, t_pt *center, int size, int color)
{
	t_pt	current;

	current.x = center->x - size;
	current.y = center->y - size;
	while (current.y <= center->y)
	{
		current.x = center->x - size;
		while (current.x <= center->x)
		{
			if (is_in_window(current.x, current.y))
				paint_pixel_blend(img, current.x, current.y, color);
			current.x++;
		}
		current.y++;
	}
}

double	get_triangle_area(t_pt *v1, t_pt *v2, t_pt *v3)
{
	return ((v1->x - v3->x) * (v2->y - v3->y)
		- (v2->x - v3->x) * (v1->y - v3->y));
}

/* Uses Barycentric coordinate algorythm */
int	is_in_triangle(t_pt *pt, t_pt *v1, t_pt *v2, t_pt *v3)
{
	double	d1;
	double	d2;
	double	d3;
	int		has_negative;
	int		has_positive;

	d1 = get_triangle_area(pt, v1, v2);
	d2 = get_triangle_area(pt, v2, v3);
	d3 = get_triangle_area(pt, v3, v1);
	has_negative = ((d1 < 0) || (d2 < 0) || (d3 < 0));
	has_positive = ((d1 > 0) || (d2 > 0) || (d3 > 0));
	return (!(has_negative && has_positive));
}

void	paint_triangle(t_img *img, t_pt v[3], int color)
{
	t_pt	min;
	t_pt	current;
	t_pt	max;

	min.x = fminf(fminf(v[0].x, v[1].x), v[2].x);
	min.y = fminf(fminf(v[0].y, v[1].y), v[2].y);
	max.x = fmaxf(fmaxf(v[0].x, v[1].x), v[2].x);
	max.y = fmaxf(fmaxf(v[0].y, v[1].y), v[2].y);
	current = min;
	while (current.y <= max.y)
	{
		current.x = min.x;
		while (current.x <= max.x)
		{
			if (is_in_triangle(&current, &v[0], &v[1], &v[2]))
				paint_pixel(img, current.x, current.y, color);
			current.x++;
		}
		current.y++;
	}
}
