/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:24:02 by mkling            #+#    #+#             */
/*   Updated: 2025/03/04 12:10:01 by mkling           ###   ########.fr       */
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
	int	row;
	int	column;
	int	offset;

	row = pt->x - UNIT;
	while (row < pt->x + UNIT)
	{
		offset = pt->x - row;
		column = pt->y - UNIT;
		while (column < pt->y + offset + UNIT)
		{
			if (is_in_window(column, row))
				paint_pixel(&cub->img, column, row, color);
			column++;
		}
		offset++;
		row++;
	}
}
