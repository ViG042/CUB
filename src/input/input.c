/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:36:06 by mkling            #+#    #+#             */
/*   Updated: 2025/04/02 10:29:14 by mkling           ###   ########.fr       */
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

int	handle_mouse(int x, int y, t_cub *cub)
{
	cub->keys.mouse_x = x;
	cub->keys.mouse_y = y;
	return (0);
}
