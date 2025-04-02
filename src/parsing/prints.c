/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:46:48 by vgodoy            #+#    #+#             */
/*   Updated: 2025/04/02 11:46:49 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (cub->elem[type].texture.mlx_img)
		{
			printf("- The %s ", talking_textures(type));
			printf("texture has been initialized\n");
		}
		else if (cub->elem[type].color >= 0)
		{
			printf("- The choosen color for the %s", talking_textures(type));
			printf(" is [%d]\n", cub->elem[type].color);
		}
		else if (cub->elem[type].back_up)
		{
			printf("- Texture or color for the %s", talking_textures(type));
			printf(" is not valid..\nBut we assigned one color for you : ");
			printf("[%d] 👀\n", cub->elem[type].back_up);
			cub->elem[type].color = cub->elem[type].back_up;
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
			c = map[line][i++];
			if (c == '1')
				printf("🎬");
			else if (c == '0')
				printf("🎹");
			else if (c == 'D')
				printf("📂");
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				printf("👹");
			else
				printf("  ");
		}
		printf("\n");
		line++;
	}
}
