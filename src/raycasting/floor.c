#include "cub.h"

int	get_color_from_texture_and_ratios(t_elem *elem, t_pt texture_position)
{
	t_pix	texture_pix;

	texture_pix.x = (int)(elem->width * texture_position.x) & (elem->width - 1);
	texture_pix.y = (int)(elem->height * texture_position.y) & (elem->height - 1);
	if (texture_pix.y < 0 || texture_pix.x < 0
		|| texture_pix.y > elem->height || texture_pix.x > elem->width)
		return (BLACK);
	else if (elem->texture.mlx_img)
		return (read_pixel(&elem->texture, elem->width,
			elem->height, texture_pix.x, texture_pix.y));
	else
		return (elem->color);
}

void	floorcasting(t_cub *cub)
{
	t_pt	floor;
	t_pt	floor_step;
	t_pt	player_dir;
	t_pt	player_plane;
	t_pt	leftmost_ray;
	t_pt	rightmost_ray;
	t_pt	texture_pos;
	int		column;
	int		row;
	int		y_distance_from_middle;
	float	row_distance;
	float	vertical_position_of_camera;
	int		cell_x;
	int		cell_y;
	int		color;


	player_dir.x = cos(cub->player.angle);
	player_dir.y = sin(cub->player.angle);
	player_plane.x = -player_dir.y * tan(FIELD_OF_VIEW / 2 * (PI / 180.0));
	player_plane.y = player_dir.x * tan(FIELD_OF_VIEW / 2 * (PI / 180.0));

	row = 0;
	while (row < WIN_HEIGHT / 2)
	{
		// Ray directions for the leftmost and rightmost rays
		leftmost_ray.x = player_dir.x - player_plane.x;
		leftmost_ray.y = player_dir.y - player_plane.y;
		rightmost_ray.x = player_dir.x + player_plane.x;
		rightmost_ray.y = player_dir.y + player_plane.y;

		// Current y position compared to the center of the screen
		y_distance_from_middle = row - WIN_HEIGHT / 2;

		// Vertical position of the camera
		vertical_position_of_camera = 0.5 * WIN_HEIGHT;

		// Horizontal distance from the camera to the floor for the current row
		row_distance = vertical_position_of_camera / y_distance_from_middle;

		// Calculate the real-world step vector for each x
		floor_step.x = row_distance * (rightmost_ray.x - leftmost_ray.x) / WIN_WIDTH;
		floor_step.y = row_distance * (rightmost_ray.y - leftmost_ray.y) / WIN_WIDTH;

		// Real-world coordinates of the leftmost column
		floor.x = cub->player.grid_pt.x + row_distance * leftmost_ray.x;
		floor.y = cub->player.grid_pt.y + row_distance * leftmost_ray.y;

		column = 0;
		while (column < WIN_WIDTH)
		{
			// Cell coordinates
			cell_x = (int)floor.x;
			cell_y = (int)floor.y;

			texture_pos.x = floor.x - cell_x;
			texture_pos.y = floor.y - cell_y;

			color = get_color_from_texture_and_ratios(&cub->elem[EA], texture_pos);
			paint_pixel(&cub->visual, column, row, color);
			color = get_color_from_texture_and_ratios(&cub->elem[WE], texture_pos);
			paint_pixel(&cub->visual, column, WIN_HEIGHT - row - 1, color);

			floor.x += floor_step.x;
			floor.y += floor_step.y;
			column++;
		}
		row++;
	}
}
