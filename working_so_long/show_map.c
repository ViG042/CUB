/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:53:25 by vgodoy            #+#    #+#             */
/*   Updated: 2024/11/29 18:34:49 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_image_1(t_var *v, int x, int y)
{
	if (v->map[y][x] == '0')
		mlx_put_image_to_window(v->mlx, v->win, v->eaux, x * 50, y * 50);
	else if (v->map[y][x] == '1')
		mlx_put_image_to_window(v->mlx, v->win, v->wall, x * 50, y * 50);
	else if (v->map[y][x] == 'P')
		mlx_put_image_to_window(v->mlx, v->win, v->fire, x * 50, y * 50);
	else if (v->map[y][x] == 'C')
		mlx_put_image_to_window(v->mlx, v->win, v->coin, x * 50, y * 50);
}

void	put_image_2(t_var *v, int x, int y)
{
	if (v->map[y][x] == 'D')
		mlx_put_image_to_window(v->mlx, v->win, v->e042, x * 50, y * 50);
	if (v->map[y][x] == 'E')
		mlx_put_image_to_window(v->mlx, v->win, v->e000, x * 50, y * 50);
	else if (v->map[y][x] == 'F')
		mlx_put_image_to_window(v->mlx, v->win, v->e025, x * 50, y * 50);
	else if (v->map[y][x] == 'G')
		mlx_put_image_to_window(v->mlx, v->win, v->e050, x * 50, y * 50);
	else if (v->map[y][x] == 'H')
		mlx_put_image_to_window(v->mlx, v->win, v->e075, x * 50, y * 50);
	else if (v->map[y][x] == 'I')
		mlx_put_image_to_window(v->mlx, v->win, v->e100, x * 50, y * 50);
	else if (v->map[y][x] == 'J')
		mlx_put_image_to_window(v->mlx, v->win, v->e125, x * 50, y * 50);
}

void	put_image_3(t_var *v, int x, int y)
{
	if (v->i_boue <= 1 || v->i_boue >= 301)
		mlx_put_image_to_window(v->mlx, v->win, v->bou1, x * 50, y * 50);
	else if (v->i_boue <= 100)
		mlx_put_image_to_window(v->mlx, v->win, v->bou2, x * 50, y * 50);
	else if (v->i_boue <= 200)
		mlx_put_image_to_window(v->mlx, v->win, v->bou3, x * 50, y * 50);
	else if (v->i_boue <= 300)
		mlx_put_image_to_window(v->mlx, v->win, v->bou4, x * 50, y * 50);
}

int	show_map(t_var *v)
{
	int	x;
	int	y;

	y = 0;
	while (y < v->y_len)
	{
		x = 0;
		while (x < v->x_len)
		{
			put_image_1(v, x, y);
			put_image_2(v, x, y);
			if (v->map[y][x] == 'B')
				put_image_3(v, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
