/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:17:21 by mkling            #+#    #+#             */
/*   Updated: 2025/03/21 01:03:24 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	get_line_len(double start_x, double start_y, double end_x, double end_y)
{
	return (sqrtf((end_x - start_x) * (end_x - start_x)
			+ (end_y - start_y) * (end_y - start_y)));
}

void	paint_column(t_cub *cub, int column)
{
	int	row;

	row = 0;
	while (row < cub->ray.top_wall)
	{
		paint_pixel(&cub->img, column, row, grad_floor_ceil(cub, row, BLUE));
		row++;
	}
	while (row < cub->ray.end_wall)
	{
		if (cub->ray.side == NORTH)
			paint_pixel(&cub->img, column, row, gradientify_wall(cub, ORANGE));
		else if (cub->ray.side == SOUTH)
			paint_pixel(&cub->img, column, row, gradientify_wall(cub, VIOLET));
		else if (cub->ray.side == WEST)
			paint_pixel(&cub->img, column, row, gradientify_wall(cub, YELLOW));
		else
			paint_pixel(&cub->img, column, row, gradientify_wall(cub, TEAL));
		row++;
	}
	while (row < WIN_HEIGHT)
	{
		paint_pixel(&cub->img, column, row, grad_floor_ceil(cub, row, GREY));
		row++;
	}
}

void	begug_print(t_cub *cub, int pixel_column)
{
	if (pixel_column == 2 ||
		pixel_column == WIN_WIDTH / 2 ||
		pixel_column == WIN_WIDTH - 2)
	{
		printf("\n\npixel column is %d\n", pixel_column);
		printf("wall hit at X=[%d] Y=[%d]\n", cub->ray.x, cub->ray.y);
		printf("On side =[%d]\n", cub->ray.side);
		printf("Wall distance =[%f]\n", cub->ray.wall_dist);
		printf("pixel_column=[%d] angle_deg=[%f] angle_rad=[%f] \
			composante_x=[%f] composante_y=[%f] first_x[%f] first_y=[%f] \
			X=[%d] Y=[%d] STEP_X=[%d] STEP_Y=[%d]\n",
			pixel_column, cub->ray.angle_deg, cub->ray.angle_deg,
			cub->ray.dist_x, cub->ray.dist_y, cub->ray.firstx, cub->ray.firsty,
			cub->ray.x, cub->ray.y, cub->ray.step_x, cub->ray.step_y);
		printf("first wall pix is %d and last is %d\n",
			cub->ray.top_wall, cub->ray.end_wall);
	}
}
