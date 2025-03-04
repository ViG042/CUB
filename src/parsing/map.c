/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:35:23 by mkling            #+#    #+#             */
/*   Updated: 2025/03/04 19:45:38 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	verify_char(t_cub *cub, int y, int x)
{
	if (cub->map->array[y][x] == '0' || cub->map->array[y][x] == '1'
			|| cub->map->array[y][x] == 'C' || cub->map->array[y][x] == 'E'
			|| cub->map->array[y][x] == 'P' || cub->map->array[y][x] == 'B')
	{
		;
	}
	else
		exit_if(1, UNKNOWN, cub);
}

static void	verify_line(t_cub *cub, int y)
{
	int	x;

	x = 0;
	while (cub->map->array[y][x])
	{
		verify_char(cub, y, x);
		x++;
	}
}

static void	set_width_and_height(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (cub->map->array[0][x])
		x++;
	cub->map->width = x;
	while (cub->map->array[y])
	{
		verify_line(cub, y);
		y++;
	}
	soft_exit_if(x > 38 || y > 20, TOO_BIG);
	cub->map->height = y;
}

static int	check_walls(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while (cub->map->array[0][x] == '1')
		x++;
	if (x != cub->map->width)
		return (0);
	x = 0;
	while (cub->map->array[cub->map->height - 1][x] == '1')
		x++;
	if (x != cub->map->width)
		return (0);
	y = 0;
	while (cub->map->array[y] && cub->map->array[y][0] == '1')
		y++;
	if (y != cub->map->height)
		return (0);
	y = 0;
	while (cub->map->array[y] && cub->map->array[y][cub->map->width - 1] == '1')
		y++;
	if (y != cub->map->height)
		return (0);
	return (1);
}

int	is_elem(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (E_NO);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (E_SO);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return (E_WE);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (E_EA);
	if (line[i] == 'F' && line[i + 1] == ' ')
		return (E_F);
	if (line[i] == 'C' && line[i + 1] == ' ')
		return (E_C);
	return (0);
}

void	load_elem(t_cub *cub, char *line, int type)
{
	int	i;
	int	size;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '.' && line[i + 1] == '/')
		i = i + 2;
	else
		return ;
	while (line[i + size] != ' ' && line[i + size] != '\n')
		size++;
	if (type == E_NO)
		cub->elem->NO = malloc(size + 1);
	if (!cub->elem->NO)
		{
			//malloc error
			return ;
		}
	

}

void	extract_elem(t_cub *cub)
{
	int	i;
	int	type;

	i = 0;
	while (cub->map->array[i])
	{
		type = is_elem(cub->map->array[i]);
		if (type)
			load_elem(cub, cub->map->array[i], type);
		i++;
	}
}

void	check_map_syntax(t_cub *cub)
{
	extract_elem(cub);
	check_elem(cub);
	copy_map(cub);
	check_map(cub);

	exit_if(!check_walls(cub), NOT_RECT, cub);
}
