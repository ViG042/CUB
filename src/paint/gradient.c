#include "cub.h"

int	gradientify_wall(t_cub *cub, int color)
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;
	double	angle;

	(void)cub;
	red = get_red(color);
	green = get_green(color);
	blue = get_blue(color);

	angle = cub->ray.angle_deg;
	if (cub->ray.side == EAST || cub->ray.side == WEST)
		angle += 90;
	angle = fmod(angle, 180);
	angle -= 90;
	angle = fabs(angle);
	angle /= 90; //range of 0 to 1
	angle = angle / 2 + 0.5;
	red = (t_byte)(red * angle);
	green = (t_byte)(green * angle);
	blue = (t_byte)(blue * angle);
	return (encode_rgb(red, green, blue));
}

int	grad_floor_ceil(t_cub *cub, int row, int color)
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;
	double	distance;

	(void)cub;
	red = get_red(color);
	green = get_green(color);
	blue = get_blue(color);

	distance = row - WIN_HEIGHT / 2;
	distance /= WIN_HEIGHT / 2;
	distance = fabs(distance);
	// distance = distance / 2 + 0.5;
	red = (t_byte)(red * distance);
	green = (t_byte)(green * distance);
	blue = (t_byte)(blue * distance);
	return (encode_rgb(red, green, blue));
}
