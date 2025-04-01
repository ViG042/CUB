/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:25 by mkling            #+#    #+#             */
/*   Updated: 2025/04/01 15:45:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_direction(t_cub *cub, t_pt *direction)
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
	rotate_direction(&direction, cub->player.angle_deg);
	check_collision(cub->map, &cub->player.grid_pt, &direction);
	cub->player.grid_pt.x += direction.x;
	cub->player.grid_pt.y += direction.y;
	cub->player.map_pt = scale_point(cub->player.grid_pt, cub->map->scale);
}
