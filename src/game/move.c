/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:25 by mkling            #+#    #+#             */
/*   Updated: 2025/04/01 12:48:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_direction(t_pt *direction, t_play *player, t_key *keys, float delta)
{
	direction->x = 0;
	direction->y = 0;
	if (keys->d)
	{
		direction->x += (2.0 * delta) * player->dir.x;
		direction->y += (2.0 * delta) * player->dir.y;
	}
	else if (keys->a)
	{
		direction->x -= (2.0 * delta) * player->dir.x;
		direction->y -= (2.0 * delta) * player->dir.y;
	}
	if (keys->s)
	{
		direction->x += (2.0 * delta) * player->plane.x;
		direction->y += (2.0 * delta) * player->plane.y;
	}
	else if (keys->w)
	{
		direction->x -= (2.0 * delta) * player->plane.x;
		direction->y -= (2.0 * delta) * player->plane.y;
	}
}

// static void	rotate_direction(t_pt *direction, float rad_angle)
// {
// 	float	cos_angle;
// 	float	sin_angle;

// 	cos_angle = cos(rad_angle);
// 	sin_angle = sin(rad_angle);
// 	direction->x = cos_angle * direction->x - sin_angle * direction->y;
// 	direction->y = sin_angle * direction->x + cos_angle * direction->y;
// }

void	move_player(t_play *player, t_key *keys, t_map *map, float delta)
{
	t_pt	direction;

	player->rad_angle = player->deg_angle * RADIAN;
	player->dir.x = cos(player->rad_angle);
	player->dir.y = sin(player->rad_angle);
	player->plane.x = -player->dir.y * tan(FIELD_OF_VIEW / 2 * RADIAN);
	player->plane.y = player->dir.x * tan(FIELD_OF_VIEW / 2 * RADIAN);
	init_direction(&direction, player, keys, delta);
	check_collision(map, &player->grid_pt, &direction);
	player->grid_pt.x += direction.x;
	player->grid_pt.y += direction.y;
}
