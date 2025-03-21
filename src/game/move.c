/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:25 by mkling            #+#    #+#             */
/*   Updated: 2025/03/21 14:58:03 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_direction(t_cub *cub, t_pt *direction)
{
	direction->x = 0;
	direction->y = 0;
	if (cub->keys.w)
		direction->y -= SPEED * cub->display.delta_time;
	else if (cub->keys.s)
		direction->y += SPEED * cub->display.delta_time;
	if (cub->keys.a)
		direction->x -= SPEED * cub->display.delta_time;
	else if (cub->keys.d)
		direction->x += SPEED * cub->display.delta_time;
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

void	move_player(t_cub *cub)
{
	t_pt	direction;

	init_direction(cub, &direction);
	rotate_direction(&direction, cub->player.player_angle);
	check_collision(cub, &direction);
	cub->player.grid_pt.x += direction.x;
	cub->player.grid_pt.y += direction.y;
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
	// printf("player is at %f %f\n", cub->player.map_pt.x, cub->player.map_pt.y);
}
