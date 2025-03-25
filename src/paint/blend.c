#include "cub.h"

t_color	split_rgb(int rgb)
{
	t_color	c;

	c.red = get_red(rgb);
	c.green = get_green(rgb);
	c.blue = get_blue(rgb);
	return (c);
}

int	merge_rgb(t_color rgb)
{
	return (encode_rgb(rgb.red, rgb.green, rgb.blue));
}

/* To avoid rgb overflow */
t_byte	mix_color(t_byte color1, t_byte color2, float ratio)
{
	int		integer;
	t_byte	result;

	integer = color1 * (1 - ratio) + color2 * ratio;
	if (integer >= 255)
		result = 255;
	else if (integer <= 0)
		result = 0;
	else
		result = (t_byte)integer;
	return (result);
}

int	blend(int color1, int color2, float ratio)
{
	t_color	c1;
	t_color	c2;
	t_color	mix;

	c1 = split_rgb(color1);
	c2 = split_rgb(color2);
	mix.red = mix_color(c1.red, c2.red, ratio);
	mix.green = mix_color(c1.green, c2.green, ratio);
	mix.blue = mix_color(c1.blue, c2.blue, ratio);
	// mix.red = c1.red * (1 - ratio) + c2.red * ratio;
	// mix.green = c1.green * (1 - ratio) + c2.green * ratio;
	// mix.blue = c1.blue * (1 - ratio) + c2.blue * ratio;
	return (merge_rgb(mix));
}

void	paint_pixel_blend(t_img *img, int x, int y, int color)
{
	int	prev_color;

	if (!is_in_window(x, y))
		return ;
	prev_color = read_pixel(img, x, y);
	paint_pixel(img, x, y, blend(prev_color, color, 0.7));
}
