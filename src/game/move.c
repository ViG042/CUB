/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:25 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 19:10:19 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

static int	collides_with_wall(t_cub *cub, t_pt destination)
{
	(void)cub;
	fprintf(stderr, "destination is %f, %f\n", destination.x, destination.y);
	return (0);
}

void	move_player(t_cub *cub)
{
	t_pt	direction;
	t_pt	destination;

	direction.x = 0;
	direction.y = 0;
	if (cub->keys.a)
		direction.x -= SPEED * cub->display.delta_time;
	else if (cub->keys.d)
		direction.x += SPEED * cub->display.delta_time;
	else if (cub->keys.s)
		direction.y += SPEED * cub->display.delta_time;
	else if (cub->keys.w)
		direction.y -= SPEED * cub->display.delta_time;
	else
		return ;
	rotate_direction(&direction, cub->player.player_angle);
	destination.x = cub->player.map_pt.x + direction.x;
	destination.y = cub->player.map_pt.y + direction.y;
	if (collides_with_wall(cub, destination))
		return ;
	cub->player.map_pt.x = destination.x;
	cub->player.map_pt.y = destination.y;
}
