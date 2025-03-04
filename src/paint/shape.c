/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:24:02 by mkling            #+#    #+#             */
/*   Updated: 2025/03/04 19:18:31 by mkling           ###   ########.fr       */
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

void	paint_square(t_cub *cub, t_pt *pt, int color)
{
	int	row;
	int	column;

	row = pt->x - UNIT;
	while (row < pt->x + UNIT)
	{
		column = pt->y - UNIT;
		while (column < pt->y + UNIT)
		{
			if (is_in_window(column, row))
				paint_pixel(&cub->img, column, row, color);
			column++;
		}
		row++;
	}
}

void	paint_triangle(t_cub *cub, t_pt *pt, int color)
{
	t_pt	top;
	t_pt	left;
	t_pt	right;

	top.x = pt->x;
	top.y = pt->y - 5;
	left.x = pt->x - 5;
	left.y = pt->y + 5;
	right.x = pt->x + 5;
	right.y = pt->y + 5;
	color = WHITE;
	rotate_point(&top, pt, cub->angle_x_axis);
	rotate_point(&left, pt, cub->angle_x_axis);
	rotate_point(&right, pt, cub->angle_x_axis);
	put_point(cub, top);
	put_point(cub, left);
	put_point(cub, right);
	paint_line(top, left, cub);
	paint_line(top, right, cub);
	paint_line(left, right, cub);
}
