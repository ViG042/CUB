/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:33:27 by mkling            #+#    #+#             */
/*   Updated: 2025/03/03 15:25:57 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

static void	check_configuration(t_cub *cub)
{
	exit_if(!check_walls(cub), NOT_WALLED, cub);
	exit_if(cub->i_player == 0, NO_PLAYER, cub);
	exit_if(cub->i_player > 1, TOO_PLAYER, cub);
}

// t_pt	turn_into_pts(char *map_point, t_cub *cub)
// {
// 	t_pt	point;
// 	char	**values;

// 	point.y = cub->map->total / cub->map->width;
// 	point.x = fmod(cub->map->total, cub->map->width);
// 	if (ft_strchr(map_point, ',') == 0)
// 	{
// 		point.z = ft_atoi(map_point);
// 		point.rgb = WHITE;
// 		return (point);
// 	}
// 	values = ft_split(map_point, ',');
// 	point.z = ft_atoi(values[0]);
// 	extract_color(&point, values[1]);
// 	ft_free_tab(values);
// 	return (point);
// }

void	parse_map(t_cub *cub)
{
	read_map_into_buffer(cub);
	cub->map->split_by_line = ft_split(cub->temp_map, '\n');
	exit_if(!cub->map->split_by_line, MALLOC_FAIL, cub);
	cub->map->array = ft_split(cub->temp_map, '\n');
	exit_if(!cub->map->array, MALLOC_FAIL, cub);
	check_configuration(cub);
}
