/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:20:40 by alex              #+#    #+#             */
/*   Updated: 2025/03/10 14:47:30 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotations(t_cub *cub)
{
	if (cub->keys.left)
		cub->player.player_angle -= SPEED * 100 * cub->display.delta_time;
	if (cub->keys.right)
		cub->player.player_angle += SPEED * 100 * cub->display.delta_time;
	if (cub->player.player_angle > 360)
		cub->player.player_angle = cub->player.player_angle / 360.00;
	if (cub->player.player_angle < -360)
		cub->player.player_angle = cub->player.player_angle / 360.00;
}

// static void	rotate_direction(t_pt *point, float angle)
// {
// 	float	radian;
// 	float	cos_angle;
// 	float	sin_angle;
// 	t_pt	rotated;

// 	radian = angle * RADIAN;
// 	cos_angle = cos(radian);
// 	sin_angle = sin(radian);
// 	rotated.x = cos_angle * point->x - sin_angle * point->y;
// 	rotated.y = sin_angle * point->x + cos_angle * point->y;
// 	point->x = rotated.x;
// 	point->y = rotated.y;
// }

// static void	movements(t_cub *cub)
// {
// 	t_pt	direction;

// 	direction.x = 0;
// 	direction.y = 0;
// 	if (cub->keys.a)
// 		direction.x -= SPEED * cub->display.delta_time;
// 	if (cub->keys.d)
// 		direction.x += SPEED * cub->display.delta_time;
// 	if (cub->keys.s)
// 		direction.y += SPEED * cub->display.delta_time;
// 	if (cub->keys.w)
// 		direction.y -= SPEED * cub->display.delta_time;

// 	rotate_direction(&direction, cub->player.player_angle);
// 	cub->player.map_pt.x += direction.x;
// 	cub->player.map_pt.y += direction.y;
// }

int	game_loop(void	*voidedcub)
{
	t_cub		*cub;
	static float counter = 0;

	cub = (t_cub *)voidedcub;
	if (cub->win == NULL)
		return (1);
	update_delta_time(cub);
	counter += cub->display.delta_time;
	if (counter > 1)
	{
		cub->display.fps = 1.0 / cub->display.delta_time;
		counter = 0;
	}
	rotations(cub);
	move_player(cub);
	render(cub);
	return (0);
}
