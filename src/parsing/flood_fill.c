/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:24:42 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/03 13:59:53 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	flood_fill(t_cub *cub, int x, int y)
{
	if (x >= cub->map->width || y >= cub->map->width
		|| cub->map->array[y][x] == '1')
		return ;
	else
	{
		// if (cub->map->array[y][x] == 'E')
		// 	cub->i_exit_copy++;
		// if (cub->map->array[y][x] == 'C')
		// 	cub->i_coin_reach++;
		cub->map->array[y][x] = '1';
	}
	if (x + 1 < cub->map->width && y < cub->map->height
		&& cub->map->array[y][x + 1] != '1')
		flood_fill(cub, x + 1, y);
	if (x - 1 < cub->map->width && y < cub->map->height
		&& cub->map->array[y][x - 1] != '1')
		flood_fill(cub, x - 1, y);
	if (x < cub->map->width && y + 1 < cub->map->height
		&& cub->map->array[y + 1][x] != '1')
		flood_fill(cub, x, y + 1);
	if (x < cub->map->width && y - 1 < cub->map->height
		&& cub->map->array[y - 1][x] != '1')
		flood_fill(cub, x, y - 1);
}

void	start_flood_fill(t_cub *cub)
{
	flood_fill(cub, cub->p_x, cub->p_y);
	// if (cub->i_exit_copy < 1)
	// 	return (errors(cub, 8));
	// if (cub->i_coin_reach * 125 / cub->i_coin < 100)
	// 	return (errors(cub, 9));
}
