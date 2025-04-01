#include "cub.h"

int	get_color_in_texture_at_pixel(t_elem *elem, t_pix *pixel)
{
	if (elem->texture.mlx_img)
		return (read_pixel(&elem->texture, elem->width,
				elem->height, pixel->x, pixel->y));
	if (pixel->y < 0 || pixel->y > elem->height
		|| pixel->x < 0 || pixel->x > elem->width)
		return (TRANSPARENT);
	else
		return (elem->color);
}

int	get_color_for_block(t_hit *block, t_elem *elem, t_pix *pixel)
{
	t_pix	texture_pix;

	texture_pix.x = (int)(block->texture_offset.x * elem->width);
	if (block->distance < 1)
		texture_pix.y = ((float)(pixel->y - block->top_pixel)
				/ (float)block->height * (float)elem->height)
			+ (float)elem->height / 2.0 * (1.0 - block->distance);
	else
		texture_pix.y = ((float)(pixel->y - block->top_pixel)
				/ (float)block->height * (float)elem->width);
	if (block->type == D)
		texture_pix.y -= elem->height * block->tile->state;
	return (get_color_in_texture_at_pixel(elem, &texture_pix));
}

void	paint_block(t_cub *cub, t_hit *block, int column, int row)
{
	t_elem	elem;
	t_pix	pixel;
	int		color;

	pixel.y = row;
	pixel.x = column;
	if (block->type != WALL)
		elem = cub->elem[block->type];
	else
		elem = cub->elem[block->side];
	color = get_color_for_block(block, &elem, &pixel);
	paint_pixel(&cub->visual, column, row, color);
}

/* P_x (Permadi) is then equal to:
P_x = px + cos(deg) * players_height *
distance_of_player_to_projection_plane *
aspect_ratio_correction_factor / dy / raFix
ar = (0.5 * screenwidth) / (5 / 8 * screenheight). (int)(0.5 * mapX * mapS) / ar */
void	paint_floor_and_ceiling(t_cub *cub, t_ray *ray, t_elem *elem, int column)
{
	t_pix	curr;
	t_pix	texture;
	float	row_distance;
	int		color;
	float	fish_eye_correction;
	// float	aspect_ratio;
	// float	correction;

	fish_eye_correction = cub->player.angle_deg - ray->angle_deg;
	if (fish_eye_correction > 360)
		fish_eye_correction = fish_eye_correction / 360.00;
	if (fish_eye_correction < 0)
		fish_eye_correction = 360 - fish_eye_correction;
	curr.y = WIN_HEIGHT / 2;
	curr.x = column;
	// aspect_ratio = (0.5 * WIN_WIDTH) / (5.0 / 8.0 * (float)WIN_HEIGHT);
	// correction = (0.5 * cub->map->width * cub->map->tile_size) / aspect_ratio;
	fish_eye_correction = cos((fish_eye_correction) * RADIAN);
	while (curr.y < WIN_HEIGHT)
	{

		row_distance = (float)WIN_HEIGHT / (2.0 * (curr.y - WIN_HEIGHT / 2.0));

        // Calculate the world position of the floor/ceiling pixel
        float world_x = cub->player.grid_pt.x + row_distance * cos(ray->angle_rad) / fish_eye_correction;
        float world_y = cub->player.grid_pt.y + row_distance * sin(ray->angle_rad) / fish_eye_correction;

        // Map the world position to texture coordinates
        texture.x = (int)(world_x * elem->width) % elem->width;
        texture.y = (int)(world_y * elem->height) % elem->height;

		// row_distance = curr.y - (WIN_HEIGHT / 2.0);

		// texture.x = cub->player.grid_pt.x / 2 + cos(ray->angle_rad) * correction
		// 	* 2 * elem->width / row_distance / fish_eye_correction;
		// texture.y = cub->player.grid_pt.y / 2 - sin(ray->angle_rad) * correction
		// 	* 2 * elem->height / row_distance / fish_eye_correction;

		// texture.x = (int)(abs(texture.x)) % (elem->width - 1);
		// texture.y = (int)(abs(texture.y)) % (elem->height - 1);

		// if (column == WIN_WIDTH / 2)
		// {
		// 	printf("elem width is %d %d\n", elem->width, elem->height);
		// 	printf("correction is %f fisheye is %f\n", correction, fish_eye_correction);
		// 	printf("texture is %d %d\n", texture.x, texture.y);
		// 	printf("row distance is %f\n", row_distance);
		// 	printf("ray angle is %f and player angle is %f\n", ray->angle_deg, cub->player.angle_deg);
		// }

		color = get_color_in_texture_at_pixel(elem, &texture);

		paint_pixel(&cub->visual, curr.x, curr.y, color);

		color = get_color_in_texture_at_pixel(elem, &texture);

		paint_pixel(&cub->visual, curr.x, WIN_HEIGHT - curr.y + 1, color);
		curr.y++;
	}
}

void	paint_column(t_cub *cub, t_hit *block, int column, int /*is_last_block*/)
{
	int	row;

	row = 0;
	row = block->top_pixel;
	while (row < block->end_pixel)
		paint_block(cub, block, column, row++);
}



	// if (column == WIN_WIDTH / 2)
		// {
		// 	printf("elem width is %d %d\n", elem->width, elem->height);
		// 	printf("correction is %f\n", correction);
		// 	printf("texture is %d %d\n", texture.x, texture.y);
		// 	printf("row distance is %f\n", row_distance);
		// }

		// floor.x = cub->player.grid_pt.x + row_distance * cos(ray->angle_rad);
		// floor.y = cub->player.grid_pt.y - row_distance * sin(ray->angle_rad);

		// texture_offset.x = floor.x - (int)floor.x;
		// texture_offset.y = floor.y - (int)floor.y;
		// texture.x = (int)(floor_hit.texture_offset.x * elem->width);
		// if (floor_hit.distance < 1)
		// 	texture.y = ((float)(curr.y - floor_hit.top_pixel)
		// 			/ (float)floor_hit.height * (float)elem->height)
		// 		+ (float)elem->height / 2.0 * (1.0 - floor_hit.distance);
		// else
		// 	texture.y = ((float)(curr.y - floor_hit.top_pixel)
		// 			/ (float)floor_hit.height * (float)elem->width);
