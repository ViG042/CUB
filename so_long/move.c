/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:26:22 by vgodoy            #+#    #+#             */
/*   Updated: 2024/11/29 18:26:30 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	transform(t_var *v, int x, int y, int param)
{
	if (param)
	{
		if (v->map[y][x] == 'E'
			&& ((v->i_coin_copy - v->i_coin) * 125 / v->i_coin_copy) >= 25)
			v->map[y][x] = 'F';
		if (v->map[y][x] == 'F'
			&& ((v->i_coin_copy - v->i_coin) * 125 / v->i_coin_copy) >= 50)
			v->map[y][x] = 'G';
		if (v->map[y][x] == 'G'
			&& ((v->i_coin_copy - v->i_coin) * 125 / v->i_coin_copy) >= 75)
			v->map[y][x] = 'H';
		if (v->map[y][x] == 'H'
			&& ((v->i_coin_copy - v->i_coin) * 125 / v->i_coin_copy) >= 100)
			v->map[y][x] = 'I';
		if (v->map[y][x] == 'I'
			&& ((v->i_coin_copy - v->i_coin) * 125 / v->i_coin_copy) >= 125)
			v->map[y][x] = 'J';
	}
	else
	{
		if (v->map[y][x] == 'E' || v->map[y][x] == 'F' || v->map[y][x] == 'G'
			|| v->map[y][x] == 'H' || v->map[y][x] == 'I'
			|| v->map[y][x] == 'J')
			v->map[y][x] = 'D';
	}
}

void	transform_exit(t_var *v, int param)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (v->map[y])
	{
		x = 0;
		while (v->map[y][x])
		{
			transform(v, x, y, param);
			x++;
		}
		y++;
	}
}

void	move_2(t_var *v)
{
	if ((v->map[v->new_y][v->new_x] == 'I' || v->map[v->new_y][v->new_x] == 'J')
			&& v->i_life > 0)
		close_window(v, 1);
	if (v->map[v->new_y][v->new_x] == 'B')
		v->i_life--;
	if (v->i_life <= 0)
		transform_exit(v, 0);
	if (v->map[v->new_y][v->new_x] == 'D')
		close_window(v, 2);
	v->map[v->p_y][v->p_x] = v->new_c;
}

void	move(t_var *v)
{
	if (v->new_x != v->p_x || v->new_y != v->p_y)
	{
		v->mvt++;
		v->new_c = v->map[v->new_y][v->new_x];
		if (v->new_c == 'C')
		{
			v->i_coin--;
			transform_exit(v, 1);
		}
		if ((v->map[v->new_y][v->new_x] >= 'D'
			&& v->map[v->new_y][v->new_x] <= 'J')
			|| v->map[v->new_y][v->new_x] == 'B')
		{
			move_2(v);
		}
		else
			v->map[v->p_y][v->p_x] = '0';
		v->map[v->new_y][v->new_x] = 'P';
		v->p_x = v->new_x;
		v->p_y = v->new_y;
	}
}
