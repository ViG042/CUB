/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:17:21 by mkling            #+#    #+#             */
/*   Updated: 2025/03/19 13:31:23 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// double	get_line_len(double start_x, double start_y, double end_x, double end_y)
// {
// 	return (sqrtf((end_x - start_x) * (end_x - start_x)
// 			+ (end_y - start_y) * (end_y - start_y)));
// }

void	calculate_wall_height(double *ray, int *step)
{
	double	min;
	double	max;
	int		int_height;

	min = 0.2;
	max = 20.0;
	int_height = (int)(((max - ray[DIST_TO_WALL]) / max) * WIN_HEIGHT);
	step[FIRST_PIXEL] = (WIN_HEIGHT - int_height) / 2;
	step[LAST_PIXEL] = step[FIRST_PIXEL] + int_height;
	step[HEIGHT] = int_height;
}

void	paint_column(t_cub *cub, int column, double *ray, int *step)
{
	int	pix;

	calculate_wall_height(ray, step);
	pix = 0;
	while (pix < step[LAST_PIXEL])
	{
		paint_pixel(&cub->img, column, pix, cub->elem[NO].color);
		pix++;
	}
}
