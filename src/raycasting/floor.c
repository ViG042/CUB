#include "cub.h"

int	get_color_from_texture_and_ratios(t_elem *elem, t_pix texture_pix)
{
	if (texture_pix.y < 0 || texture_pix.x < 0
		|| texture_pix.y > elem->height || texture_pix.x > elem->width)
		return (BLACK);
	else if (elem->texture.mlx_img)
		return (read_pixel(&elem->texture, elem->width,
				elem->height, texture_pix.x, texture_pix.y));
	else
		return (elem->color);
}

// void	paint_floor_and_ceiling(t_cub *cub, t_pt floor, int column, int row)
// {

// 	color = get_color_from_texture_and_ratios(&cub->elem[EA], texture_pix);
// 	paint_pixel(&cub->visual, column, row, color);
// 	color = get_color_from_texture_and_ratios(&cub->elem[WE], texture_pix);
// 	paint_pixel(&cub->visual, column, WIN_HEIGHT - row - 1, color);
// }

void	floorcasting(t_cub *cub)
{
	t_pt	floor;
	t_pt	floor_step;
	t_pt	leftmost_ray;
	t_pt	rightmost_ray;
	int		column;
	int		row;
	int		y_distance_from_middle;
	float	row_distance;
	float	height_of_player;
	int		cell_x;
	int		cell_y;
	int		color;
	t_pix	texture_pix;


	row = 0;
	while (row < WIN_HEIGHT)
	{
		// Ray directions for the leftmost and rightmost rays
		leftmost_ray.x = cub->player.dir.x - cub->player.plane.x;
		leftmost_ray.y = cub->player.dir.y - cub->player.plane.y;
		rightmost_ray.x = cub->player.dir.x + cub->player.plane.x;
		rightmost_ray.y = cub->player.dir.y + cub->player.plane.y;

		// Current y position compared to the center of the screen
		y_distance_from_middle = row - ((float)WIN_HEIGHT / 2.0);

		height_of_player = 0.5 * (float)WIN_HEIGHT;

		// Horizontal distance from the camera to the floor for the current row
		row_distance = height_of_player / (float)y_distance_from_middle;

		// Calculate the real-world step vector for each x
		floor_step.x = row_distance * (rightmost_ray.x - leftmost_ray.x) / WIN_WIDTH;
		floor_step.y = row_distance * (rightmost_ray.y - leftmost_ray.y) / WIN_WIDTH;

		// Real-world coordinates of the leftmost column
		floor.x = cub->player.grid_pt.x + row_distance * leftmost_ray.x;
		floor.y = cub->player.grid_pt.y + row_distance * leftmost_ray.y;

		column = 0;
		while (column < WIN_WIDTH)
		{
			cell_x = (int)floor.x;
			cell_y = (int)floor.y;
			texture_pix.x = (int)(cub->elem[EA].width * (floor.x - cell_x)) % (cub->elem[EA].width - 1);
			texture_pix.y = (int)(cub->elem[EA].height * (floor.y - cell_y)) % (cub->elem[EA].height - 1);

			floor.x += (float)floor_step.x;
			floor.y += (float)floor_step.y;

			color = get_color_from_texture_and_ratios(&cub->elem[EA], texture_pix);
			paint_pixel(&cub->visual, column, row, color);

			if (row == WIN_HEIGHT / 2 + 2 && column == WIN_WIDTH / 2 + 2)
			{
				printf("floor is %f, %f\n", floor.x, floor.y);
				printf("texture is %d, %d\n", texture_pix.x, texture_pix.y);
				printf("height is %f and row distance is %f\n", height_of_player, row_distance);
				printf("y is %d \n", y_distance_from_middle);
				printf("floorcasting: player.dir: (%f, %f), player.plane: (%f, %f)\n",
					cub->player.dir.x, cub->player.dir.y, cub->player.plane.x, cub->player.plane.y);

			}


			column++;
		}
		row++;
	}
}
