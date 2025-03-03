/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:26:22 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/03 11:37:33 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	verify_char(t_cub *v, int y, int x)
{
	if (v->map[y][x] == '0' || v->map[y][x] == '1'
			|| v->map[y][x] == 'C' || v->map[y][x] == 'E'
			|| v->map[y][x] == 'P' || v->map[y][x] == 'B')
	{
		if (v->map[y][x] == 'P')
		{
			v->i_player++;
			v->new_y = y;
			v->new_x = x;
			v->new_c = '0';
			v->p_x = x;
			v->p_y = y;
		}
		if (v->map[y][x] == 'E')
			v->i_exit++;
		if (v->map[y][x] == 'C')
		{
			v->i_coin++;
			v->i_coin_copy++;
			v->i_life++;
		}
	}
	else
		return (errors(v, 11));
	return (1);
}

int	verify_line(t_cub *v, int y)
{
	int	x;

	x = 0;
	while (v->map[y][x])
	{
		if (!verify_char(v, y, x))
			return (0);
		x++;
	}
	if (x != v->x_len)
		return (errors(v, 4));
	return (1);
}

int	get_width_and_height(t_cub *v)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (v->map[0][x])
		x++;
	v->x_len = x;
	while (v->map[y])
	{
		if (!verify_line(v, y))
			return (0);
		y++;
	}
	if (x > 38 || y > 20)
		return (errors(v, 2));
	v->y_len = y;
	return (1);
}

int	check_walls(t_cub *v)
{
	int	x;
	int	y;

	x = 0;
	while (v->map[0][x] == '1')
		x++;
	if (x != v->x_len)
		return (0);
	x = 0;
	while (v->map[v->y_len - 1][x] == '1')
		x++;
	if (x != v->x_len)
		return (0);
	y = 0;
	while (v->map[y] && v->map[y][0] == '1')
		y++;
	if (y != v->y_len)
		return (0);
	y = 0;
	while (v->map[y] && v->map[y][v->x_len - 1] == '1')
		y++;
	if (y != v->y_len)
		return (0);
	return (1);
}
