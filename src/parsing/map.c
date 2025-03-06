/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:35:23 by mkling            #+#    #+#             */
/*   Updated: 2025/03/06 19:44:31 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_map(t_cub *cub)
{
	(void)cub;
}

int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
	{
		return (1);
	}
	return (0);
}

int	is_valid_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_valid_char(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	not_yet(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] == '1')
		counter++;
	while (str[i] && is_valid_char(str[i]))
		i++;
	if (!str[i] && counter >= 3)
		return (0);
	return (1);
}

// exit_if(!cub->map->array[line], NO_MAP, cub);
// exit_if(!is_valid_line(cub->map->array[line]), MAP_NOT_VALID, cub);

void	clean_map(t_cub *cub)
{
	int	line;
	int	i;

	line = 0;
	i = 0;
	printf("in clean_map[%d]\n\n", line);
	while (cub->map->array[line] && line < 19)
	{
		printf("cub->map->array[%d]=[%s]\n\n", line, cub->map->array[line]);////
		line++;
	}
	line--;
	printf("i=[%d] line=[%d]", i, line);////
	//exit_if(!is_valid_line(cub->map->array[line]), NO_MAP, cub);
	while (is_valid_line(cub->map->array[line]))
	{
		printf("i=[%d] line=[%d]", i, line);///////
		free(cub->map->array[i]);
		cub->map->array[i] = cub->map->array[line];
		i++;
		line--;
	}
	while (cub->map->array[i])
	{
		cub->map->array[i] = NULL;
		i++;
	}
}

// void	clean_map(t_cub *cub)
// {
// 	int	map_start;
// 	int	map_end;

// 	map_start = start_mapping(cub);
// 	map_end = stop_mapping(cub, map_start);
// 	while (map_start <= map_end)
// 	{
// 		map_start++;
// 	}
// 	// int	line;
// 	// int	i;

// 	// line = 0;
// 	// while ()
// }
/*
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
*/
