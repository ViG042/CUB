/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:17:21 by mkling            #+#    #+#             */
/*   Updated: 2025/03/20 18:21:53 by mkling           ###   ########.fr       */
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
		paint_pixel(&cub->img, column, row, ORANGE / 4);
		row++;
	}
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
	while (row < WIN_HEIGHT)
	{
		paint_pixel(&cub->img, column, row, ORANGE * 2);
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
		printf("LAST_MOVE=[%d]\n", cub->ray.side);
		// printf("ray[DIST_TO_WALL]=[%f]\n\n", ray[DIST_TO_WALL]);
		// printf("pixel_column=[%d] angle_deg=[%f] angle_rad=[%f] \
		// 	composante_x=[%f] composante_y=[%f] first_x[%f] first_y=[%f] \
		// 	X=[%d] Y=[%d] STEP_X=[%d] STEP_Y=[%d]\n",
		// 	pixel_column, ray[ANGLE_DEG], ray[ANGLE_RAD],
		// 	ray[DIST_X], ray[DIST_Y], ray[FIRST_X], ray[FIRST_Y],
		// 	step[X], step[Y], step[STEP_X], step[STEP_Y]);
		printf("first wall pix is %d and last is %d\n", cub->ray.top_wall, cub->ray.end_wall);
	}
}

// void paint_column(t_cub *cub, int *step, int pixel_column)
// {
// 	int c;

// 	c = 0;
// 	while (c < step[FIRST_PIXEL])
// 	{
// 		paint_pixel(&cub->img, pixel_column, c, ORANGE / 4);
// 		c++;
// 	}
// 	while (c < step[LAST_PIXEL])
// 	{
// 		if (step[LAST_MOVE] == NORTH)
// 			paint_pixel(&cub->img, pixel_column, c, WHITE);
// 		else if (step[LAST_MOVE] == SOUTH)
// 			paint_pixel(&cub->img, pixel_column, c, DARK_GREY);
// 		else if (step[LAST_MOVE] == WEST)
// 			paint_pixel(&cub->img, pixel_column, c, ORANGE);
// 		else
// 			paint_pixel(&cub->img, pixel_column, c, ORANGE / 2);
// 		c++;
// 	}
// 	while (c < WIN_HEIGHT)
// 	{
// 		paint_pixel(&cub->img, pixel_column, c, ORANGE * 2);
// 		c++;
// 	}
// }
