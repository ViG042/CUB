/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:36:06 by mkling            #+#    #+#             */
/*   Updated: 2025/03/08 23:22:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"



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

int	handle_input(int keysym, int mode, t_cub *cub)
{
	bool	state;

	state = 0;
	if (mode == KeyPressMask)
		state = 1;
	fprintf(stderr, "I love you %i %i\n", keysym, mode);
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
