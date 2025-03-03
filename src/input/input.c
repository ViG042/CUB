/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:36:06 by mkling            #+#    #+#             */
/*   Updated: 2025/03/03 15:24:42 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotations(int keysym, t_cub *cub)
{
	if (keysym == XK_r)
		cub->angle_x_axis += 0.05;
	if (keysym == XK_f)
		cub->angle_x_axis -= 0.05;
	if (keysym == XK_t)
		cub->angle_z_axis += 0.05;
	if (keysym == XK_g)
		cub->angle_z_axis -= 0.05;
	if (keysym == XK_Left)
		cub->angle_y_axis += 0.05;
	if (keysym == XK_Right)
		cub->angle_y_axis -= 0.05;
}

int	handle_mouse(int button, int x, int y, t_cub *cub)
{
	// if (button == WHEEL_UP || button == WHEEL_DOWN)
	// 	zoom(button, cub);
	if (button == LEFT_CLICK)
		mlx_string_put(cub->mlx, cub->win, x, y, WHITE, "Left Click");
	render(cub);
	return (0);
}

int	handle_input(int keysym, t_cub *cub)
{
	rotations(keysym, cub);
	if (keysym == XK_Escape)
		success_exit(cub);
	// if (keysym == XK_Up)
	// 	zoom(keysym, cub);
	// if (keysym == XK_Down)
	// 	zoom(keysym, cub);
	if (keysym == XK_a)
		cub->offset_x -= 10;
	if (keysym == XK_d)
		cub->offset_x += 10;
	if (keysym == XK_s)
		cub->offset_y += 10;
	if (keysym == XK_w)
		cub->offset_y -= 10;
	render(cub);
	return (0);
}
