/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:36:06 by mkling            #+#    #+#             */
/*   Updated: 2025/03/28 10:55:54 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	handle_input(int keysym, int mode, t_cub *cub)
{
	bool	state;

	state = 0;
	if (mode == KeyPressMask)
		state = 1;
	if (keysym == XK_a)
		cub->keys.a = state;
	if (keysym == XK_d)
		cub->keys.d = state;
	if (keysym == XK_s)
		cub->keys.s = state;
	if (keysym == XK_w)
		cub->keys.w = state;
	if (keysym == XK_Left)
		cub->keys.left = state;
	if (keysym == XK_Right)
		cub->keys.right = state;
	if (keysym == XK_Escape)
		success_exit(cub);
	return (0);
}

int	handle_input_press(int keysym, t_cub *cub)
{
	handle_input(keysym, KeyPressMask, cub);
	return (0);
}

int	handle_input_release(int keysym, t_cub *cub)
{
	handle_input(keysym, KeyReleaseMask, cub);
	return (0);
}

void	capture_mouse(int x, int y, t_cub *cub)
{
	if (x < 0)
		mlx_mouse_move(cub->mlx, cub->win, 0, y);
	if (y < 0)
		mlx_mouse_move(cub->mlx, cub->win, x, 0);
	if (x > WIN_WIDTH)
		mlx_mouse_move(cub->mlx, cub->win, WIN_WIDTH, y);
	if (y > WIN_HEIGHT)
		mlx_mouse_move(cub->mlx, cub->win, x, WIN_HEIGHT);
}

int	handle_mouse(int x, int y, t_cub *cub)
{
	cub->keys.mouse_x = cub->display.mid_x;
	cub->keys.mouse_y = cub->display.mid_y;
	// printf("mouse is x=[%d] y=[%d]\n", x, y);
	capture_mouse(x, y, cub);
	cub->keys.mouse_x = x;
	cub->keys.mouse_y = y;
	return (0);
}


