/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:25 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 21:13:16 by mkling           ###   ########.fr       */
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

static int	is_wall(t_cub *cub, int x, int y)
{
	if (x < MINIMAP_OFFSET || y < MINIMAP_OFFSET
		|| x >= cub->minimap->width || y >= cub->minimap->height)
		return (1);
	// printf("map is %c\n", cub->map->clean_map[x][y]);
	return (0);
}

static int	collides_with_wall(t_cub *cub, t_pt direction)
{
	t_pt	destination;

	printf("player is %f %f\n", cub->player.grid_pt.x, cub->player.grid_pt.y);
	printf("direction is %f %f\n", direction.x, direction.y);
	destination.x = cub->player.map_pt.x + direction.x;
	destination.y = cub->player.map_pt.y + direction.y;
	printf("destination is %f %f\n", destination.x, destination.y);
	if (is_wall(cub, (int)destination.x, (int)destination.y))
		return (1);
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
	if (collides_with_wall(cub, direction))
		return ;
	// cub->player.grid_pt.x += direction.x;
	// cub->player.grid_pt.y += direction.y;
	// cub->player.map_pt = project_point(cub, cub->player.grid_pt);
	cub->player.map_pt.x += direction.x;
	cub->player.map_pt.y += direction.y;
}
