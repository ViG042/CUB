/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:24:42 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/03 18:12:03 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	flood_fill(t_cub *cub, int x, int y)
{
	if (x >= cub->map->width || y >= cub->map->width
		|| cub->map->array[y][x] == '1')
		return ;
	else
		cub->map->array[y][x] = '1';
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
