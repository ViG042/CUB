/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:24:02 by mkling            #+#    #+#             */
/*   Updated: 2025/03/08 22:10:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	paint_square(t_img *img, t_pt *bottom_left, int size, int color)
{
	t_pt	current;

	current.x = bottom_left->x - size;
	current.y = bottom_left->y - size;
	while (current.y <= bottom_left->y)
	{
		current.x = bottom_left->x - size;
		while (current.x <= bottom_left->x)
		{
			if (is_in_window(current.x, current.y))
				paint_pixel(img, current.x, current.y, color);
			current.x++;
		}
		current.y++;
	}
}

float	get_triangle_area(t_pt *v1, t_pt *v2, t_pt *v3)
{
	return ((v1->x - v3->x) * (v2->y - v3->y)
		- (v2->x - v3->x) * (v1->y - v3->y));
}

/* Uses Barycentric coordinate algorythm */
int	is_in_triangle(t_pt *pt, t_pt *v1, t_pt *v2, t_pt *v3)
{
	float	d1;
	float	d2;
	float	d3;
	int		has_negative;
	int		has_positive;

	d1 = get_triangle_area(pt, v1, v2);
	d2 = get_triangle_area(pt, v2, v3);
	d3 = get_triangle_area(pt, v3, v1);
	has_negative = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_positive = (d1 > 0) || (d2 > 0) || (d3 > 0);
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

void	orient_and_paint_player(t_cub *cub, t_pt *center, int size, int color)
{
	t_pt	vertex[3];

	vertex[TOP].x = center->x;
	vertex[TOP].y = center->y - size * 0.1;
	vertex[LEFT].x = center->x - size;
	vertex[LEFT].y = center->y + size;
	vertex[RIGHT].x = center->x + size;
	vertex[RIGHT].y = center->y + size;
	rotate_point(cub, &vertex[TOP], center, cub->player_angle);
	rotate_point(cub, &vertex[LEFT], center, cub->player_angle);
	rotate_point(cub, &vertex[RIGHT], center, cub->player_angle);
	// put_point(cub, vertex[TOP]);
	// put_point(cub, vertex[LEFT]);
	// put_point(cub, vertex[RIGHT]);
	// paint_line(vertex[TOP], vertex[LEFT], cub);
	// paint_line(vertex[TOP], vertex[RIGHT], cub);
	// paint_line(vertex[LEFT], vertex[RIGHT], cub);
	paint_triangle(&cub->img, vertex, color);
}
