/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:25 by mkling            #+#    #+#             */
/*   Updated: 2025/03/20 18:54:56 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_direction(t_cub *cub, t_pt *direction)
{
	double	step;

	step = 0.01;
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


/*			printf("cub->map->pts[y=%d][x=%d].type == '1'\n", y, x);///////*/
static int	is_wall(t_cub *cub, int x, int y)
{
	if (cub->map->pts[y][x].type)
	{
		if (cub->map->pts[y][x].type == '1')
			return (1);
		if (cub->map->pts[y][x].type == 'D')
			return (1);
	}
	return (0);
}

/*		printf("where=[%d], dist=[%f]\n", where, dist);*/
int	too_close(double x, double y, int where)
{
	double	wand;
	double	dist;

	wand = WAND;
	dist = 1;
	if (where == NORTH)
		dist = y - floor(y);
	else if (where == SOUTH)
		dist = ceil(y) - y;
	else if (where == WEST)
		dist = x - floor(x);
	else if (where == EAST)
		dist = ceil(x) - x;
	if (dist < wand)
		return (1);
	return (0);
}

/*Pour chacune des 4 directions
Si un mouvement se fait dans cette direction
Si une case plus loin dans cette direction on a un mur
Si la procimite a ce mur est inferieur a wand
Alors on annule le mouvement dans cette direction
	printf("player position x=[%f] y=[%f]\n\n", x ,y);///*/
void	check_edges(t_cub *cub, t_pt *direction)
{
	double	x;
	double	y;

	x = cub->player.grid_pt.x;
	y = cub->player.grid_pt.y;
	if (direction->y < 0
		&& is_wall(cub, x, y - 1)
		&& too_close(x, y, NORTH))
		direction->y = 0;
	else if (direction->y > 0
		&& is_wall(cub, x, y + 1)
		&& too_close(x, y, SOUTH))
		direction->y = 0;
	if (direction->x < 0
		&& is_wall(cub, x - 1, y)
		&& too_close(x, y, WEST))
		direction->x = 0;
	else if (direction->x > 0
		&& is_wall(cub, x + 1, y)
		&& too_close(x, y, EAST))
		direction->x = 0;
}

void	move_player(t_cub *cub)
{
	t_pt	direction;

	init_direction(cub, &direction);
	rotate_direction(&direction, cub->player.player_angle);
	check_edges(cub, &direction);
	cub->player.grid_pt.x += direction.x;
	cub->player.grid_pt.y += direction.y;
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
