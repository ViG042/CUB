/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:36:06 by mkling            #+#    #+#             */
/*   Updated: 2025/03/05 16:54:49 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotations(int keysym, t_cub *cub)
{
	if (keysym == XK_Left)
		cub->angle_x_axis += 5;
	if (keysym == XK_Right)
		cub->angle_x_axis -= 5;
}

int	handle_mouse(int button, int x, int y, t_cub *cub)
{
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
	if (keysym == XK_a)
		cub->player.x -= 5;
	if (keysym == XK_d)
		cub->player.x += 5;
	if (keysym == XK_s)
		scale_2dvector(&cub->player, 0.95);
	if (keysym == XK_w)
		scale_2dvector(&cub->player, 1.01);
	render(cub);
	return (0);
}
