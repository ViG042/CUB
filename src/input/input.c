/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:36:06 by mkling            #+#    #+#             */
/*   Updated: 2025/03/06 22:23:30 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotations(int keysym, t_cub *cub)
{
	if (keysym == XK_Left)
		cub->angle_x_axis -= 5;
	if (keysym == XK_Right)
		cub->angle_x_axis += 5;
}

static void	rotate_direction(t_pt *point, float angle)
{
	float	radian;
	float	cos_angle;
	float	sin_angle;
	t_pt	rotated;

	radian = angle * RADIAN;
	cos_angle = cos(radian);
	sin_angle = sin(radian);
	rotated.x = cos_angle * point->x - sin_angle * point->y;
	rotated.y = sin_angle * point->x + cos_angle * point->y;
	point->x = rotated.x;
	point->y = rotated.y;
}

static void	movements(int keysym, t_cub *cub)
{
	t_pt	direction;

	direction.x = 0;
	direction.y = 0;
	if (keysym == XK_a)
		direction.x -= 5;
	if (keysym == XK_d)
		direction.x += 5;
	if (keysym == XK_s)
		direction.y += 5;
	if (keysym == XK_w)
		direction.y -= 5;

	rotate_direction(&direction, cub->angle_x_axis);
	cub->player.x += direction.x;
	cub->player.y += direction.y;
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
	movements(keysym, cub);
	if (keysym == XK_Escape)
		success_exit(cub);
	render(cub);
	return (0);
}
