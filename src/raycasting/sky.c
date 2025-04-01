#include "cub.h"

void	paint_lil_square(t_img *img, t_pix *upleft, int size, int color)
{
	t_pix	current;

	current.y = upleft->y;
	while (current.y <= upleft->y + size)
	{
		current.x = upleft->x;
		while (current.x <= upleft->x + size)
		{
			if (is_in_window(current.x, current.y))
				paint_pixel(img, current.x, current.y, color);
			current.x++;
		}
		current.y++;
	}
}

void	paint_sky(t_img *img, t_elem *sky, t_play *player)
{
	int		ratio;
	int		color;
	int		pixel_size;
	t_pix	pixel;
	t_pix	texture;
	t_pix	scaled;

	pixel.y = 0;
	pixel_size = 8;
	while (pixel.y < sky->width)
	{
		pixel.x = 0;
		while (pixel.x < sky->width)
		{
			ratio = (int)(player->angle_deg * 2) - pixel.x;
			if (ratio < 0)
				ratio += sky->width;
			ratio = ratio % sky->width;
			texture.x = ratio;
			texture.y = pixel.y;
			color = read_pixel(&sky->texture,
					sky->width, sky->height, texture.x, texture.y);
			scaled.x = pixel.x * pixel_size;
			scaled.y = pixel.y * pixel_size;
			for (int dy = 0; dy < pixel_size; dy++)
			{
				for (int dx = 0; dx < pixel_size; dx++)
				{
					paint_pixel(img, scaled.x + dx, scaled.y + dy, color);
				}
			}
			pixel.x++;
		}
		pixel.y++;
	}
}
