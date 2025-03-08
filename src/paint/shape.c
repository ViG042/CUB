/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:24:02 by mkling            #+#    #+#             */
/*   Updated: 2025/03/08 15:21:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	paint_square(t_img *img, t_pt *center, int size, int color)
{
	t_pt	current;

	current.x = center->x - size;
	current.y = center->y - size;
	while (current.y <= center->y + size)
	{
		while (current.x <= center->x + size)
		{
			if (is_in_window(current.x, current.y))
				paint_pixel(img, current.x, current.y, color);
			current.x++;
		}
		current.y++;
	}
}

void	find_top_bottom_triangle(t_pt *pt1, t_pt *pt2, t_pt *pt3, t_pt result[3])
{
	t_pt	*top;
	t_pt	*bottom;

	if (pt1->y <= pt2->y && pt1->y <= pt3->y)
		top = pt1;
	else if (pt2->y <= pt1->y && pt2->y <= pt3->y)
		top = pt2;
	else
		top = pt3;
	if (pt1->y >= pt2->y && pt1->y >= pt3->y)
		bottom = pt1;
	else if (pt2->y >= pt1->y && pt2->y >= pt3->y)
		bottom = pt2;
	else
		bottom = pt3;
	if (pt1 != top && pt1 != bottom)
		result[MID] = *pt1;
	else if (top != pt2 && bottom != pt2)
		result[MID] = *pt2;
	else
		result[MID] = *pt3;
	result[TOP] = *top;
	result[BOTTOM] = *bottom;
}

void	paint_triangle(t_img *img, t_pt pt[3], int color)
{
	t_pt	current;
	float	slope_left;
	float	slope_right;
	int		end_of_x;

	slope_left = (float)(pt[MID].x - pt[TOP].x) / (pt[MID].y - pt[TOP].y);
	slope_right = (float)(pt[BOTTOM].x - pt[TOP].x) / (pt[BOTTOM].y - pt[TOP].y);
	while (current.y <= pt[MID].y)
	{
		current.x = pt[TOP].x + (current.y - pt[TOP].y) * slope_left;
		end_of_x = pt[TOP].x + (current.y - pt[TOP].y) * slope_right;
		while (current.x <= end_of_x)
			paint_pixel(img, current.x++, current.y, color);
		current.y++;
	}
	slope_left = (float)(pt[BOTTOM].x - pt[MID].x) / (pt[BOTTOM].y - pt[MID].y);
	current.y = pt[MID].y;
	while (current.y <= pt[BOTTOM].y)
	{
		current.x = pt[MID].x + (current.y - pt[MID].y) * slope_left;
		end_of_x = pt[TOP].x + (current.y - pt[TOP].y) * slope_right;
		while (current.x <= end_of_x)
			paint_pixel(img, current.x++, current.y, color);
		current.y++;
	}
}

void	orient_and_paint_player(t_cub *cub, t_pt *center, int size, int color)
{
	t_pt	top;
	t_pt	left;
	t_pt	right;
	t_pt	coordinates[3];

	top.x = center->x;
	top.y = center->y - size;
	left.x = center->x - size;
	left.y = center->y + size;
	right.x = center->x + size;
	right.y = center->y + size;
	rotate_point(cub, &top, center, cub->angle_x_axis);
	rotate_point(cub, &left, center, cub->angle_x_axis);
	rotate_point(cub, &right, center, cub->angle_x_axis);
	put_point(cub, top);
	put_point(cub, left);
	put_point(cub, right);
	paint_line(top, left, cub);
	paint_line(top, right, cub);
	paint_line(left, right, cub);
	find_top_bottom_triangle(&top, &left, &right, coordinates);
	paint_triangle(&cub->img, coordinates, color);
}
