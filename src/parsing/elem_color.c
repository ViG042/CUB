#include "cub.h"

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

int	color_atoi(char *str)
{
	int	i;
	int	color;

	i = 0;
	color = 0;
	if (str[0] && str[0] >= '0' && str[0] <= '9')
		color = str[0] - '0';
	else
		return (-1);
	if (str[1] && str[1] >= '0' && str[1] <= '9')
	{
		color = color * 10 + str[1] - '0';
		if (str[2] && str[2] >= '0' && str[2] <= '9')
		{
			color = color * 10 + str[2] - '0';
			if (str[3] && str[3] >= '0' && str[3] <= '9')
				return (-1);
		}
	}
	if (color > 255)
		return (-1);
	return (color);
}

int	make_color(char *description)
{
	int	red;
	int	green;
	int	blue;
	int	i;

	i = 0;
	printf("\nthe color to parse is [%s]\n", description);/////////
	red = color_atoi(&description[i]);
	printf("red=[%d]\n", red);////////////
	while (description[i] && description[i] >= '0' && description[i] <= '9')
		i++;
	if (description[i] == ',')
		i++;
	else
		return (-1);
	green = color_atoi(&description[i]);
	printf("green=[%d]\n", green);////////////
	while (description[i] && description[i] >= '0' && description[i] <= '9')
		i++;
	if (description[i] == ',')
		i++;
	else
		return (-1);
	blue = color_atoi(&description[i]);
	printf("blue=[%d]\n", blue);////////////
	if (red == -1 || green == -1 || blue == -1)
		return (-1);
	else
		return (encode_rgb(red, green, blue));
}
