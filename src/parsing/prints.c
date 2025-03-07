#include "cub.h"

char	*talking_textures(int type)
{
	if (type == NO)
		return ("north");
	if (type == SO)
		return ("south");
	if (type == WE)
		return ("west");
	if (type == EA)
		return ("east");
	if (type == F)
		return ("floor");
	if (type == C)
		return ("ceiling");
	if (type == D)
		return ("doors");
	return ("(what?)");
}

void	print_info(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s/n\n", array[i]);
		i++;
	}
	printf("\n🚀 Informations have been fetched\n\n");
}

void	print_elem(t_cub *cub)
{
	int	i;

	i = NO;
	while (i <= D)
	{
		printf("The %s description : ", talking_textures(i));
		printf("%s\n", cub->elem[i].description);
		i++;
	}
	printf("\n🚀 Element's informations extraction done\n\n");
}

void	print_init_elem(t_cub *cub)
{
	int	type;

	type = NO;
	while (type <= D)
	{
		if (cub->elem[type].texture)
		{
			printf("- The %s", talking_textures(type));
			printf("texture has been initialized\n");
		}
		else if (cub->elem[type].color)
		{
			printf("- The choosen color for the %s", talking_textures(type));
			printf(" is [%d]\n", cub->elem[type].color);
		}
		else if (cub->elem[type].back_up)
		{
			printf("- Texture or color for the %s", talking_textures(type));
			printf(" is not valid..\nBut we assigned one color for you : ");
			printf("[%d] 👀\n", cub->elem[type].back_up);
		}
		type++;
	}
	printf("\n🚀 Elements have been initialized\n\n");
}

void	print_map(char **map)
{
	int		line;
	int		i;
	char	c;

	line = 0;
	while (map[line])
	{
		i = 0;
		while (map[line][i])
		{
			c = map[line][i];
			if (c == '1')
				printf("🎬");
			else if (c == '0')
				printf("🎹");
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				printf("👹");
			else
				printf("  ");
			i++;
		}
		printf("\n");
		line++;
	}
	printf("\n🚀 Map has been cleaned !\n\n");
}
