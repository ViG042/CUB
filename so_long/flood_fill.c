/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:24:42 by vgodoy            #+#    #+#             */
/*   Updated: 2024/11/29 17:53:50 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	flood_fill(t_var *v, int x, int y)
{
	if (x >= v->x_len || y >= v->y_len || v->map_copy[y][x] == '1')
		return ;
	else
	{
		if (v->map_copy[y][x] == 'E')
			v->i_exit_copy++;
		if (v->map_copy[y][x] == 'C')
			v->i_coin_reach++;
		v->map_copy[y][x] = '1';
	}
	if (x + 1 < v->x_len && y < v->y_len && v->map_copy[y][x + 1] != '1')
		flood_fill(v, x + 1, y);
	if (x - 1 < v->x_len && y < v->y_len && v->map_copy[y][x - 1] != '1')
		flood_fill(v, x - 1, y);
	if (x < v->x_len && y + 1 < v->y_len && v->map_copy[y + 1][x] != '1')
		flood_fill(v, x, y + 1);
	if (x < v->x_len && y - 1 < v->y_len && v->map_copy[y - 1][x] != '1')
		flood_fill(v, x, y - 1);
	return ;
}

int	start_flood_fill(t_var *v)
{
	flood_fill(v, v->p_x, v->p_y);
	if (v->i_exit_copy < 1)
		return (errors(v, 8));
	if (v->i_coin_reach * 125 / v->i_coin < 100)
		return (errors(v, 9));
	return (1);
}
