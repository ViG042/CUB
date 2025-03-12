/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:25 by mkling            #+#    #+#             */
/*   Updated: 2025/03/12 16:35:37 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotate_direction(t_pt *point, double angle)
{
	double	radian;
	double	cos_angle;
	double	sin_angle;
	t_pt	rotated;

	radian = angle * RADIAN;
	cos_angle = cos(radian);
	sin_angle = sin(radian);
	rotated.x = cos_angle * point->x - sin_angle * point->y;
	rotated.y = sin_angle * point->x + cos_angle * point->y;
	point->x = rotated.x;
	point->y = rotated.y;
}

static int	is_wall(t_cub *cub, t_pt dest)
{
	int	round_y;
	int	round_x;

	if (dest.x < 0 || dest.y < 0 || dest.x >= cub->map->width
		|| dest.y >= cub->map->height)
		return (1);
	round_y = (int)round(dest.y);
	round_x = (int)round(dest.x);
	if (cub->map->pts[round_y][round_x].type)
	{
		if (cub->map->pts[round_y][round_x].type == '1')
			return (1);
		if (cub->map->pts[round_y][round_x].type == 'D')
			return (1);
	}
	return (0);
}

void	move_player(t_cub *cub)
{
	t_pt	direction;

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
	direction.x += cub->player.grid_pt.x;
	direction.y += cub->player.grid_pt.y;
	if (is_wall(cub, direction))
		return ;
	cub->player.grid_pt.x = direction.x;
	cub->player.grid_pt.y = direction.y;
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
