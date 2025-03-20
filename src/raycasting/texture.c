/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:17:21 by mkling            #+#    #+#             */
/*   Updated: 2025/03/20 15:51:45 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	get_line_len(double start_x, double start_y, double end_x, double end_y)
{
	return (sqrtf((end_x - start_x) * (end_x - start_x)
			+ (end_y - start_y) * (end_y - start_y)));
}

void	paint_wall(t_cub *cub, int column)
{
	int	row;

	row = cub->ray.top_wall;
	while (row < cub->ray.end_wall)
	{
		if (cub->ray.side == NORTH)
			paint_pixel(&cub->img, column, row, WHITE);
		else if (cub->ray.side == SOUTH)
			paint_pixel(&cub->img, column, row, DARK_GREY);
		else if (cub->ray.side == WEST)
			paint_pixel(&cub->img, column, row, ORANGE);
		else
			paint_pixel(&cub->img, column, row, ORANGE / 2);
		row++;
	}
}
