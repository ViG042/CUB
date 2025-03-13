/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:25 by mkling            #+#    #+#             */
/*   Updated: 2025/03/13 12:12:11 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	init_direction(t_cub *cub, t_pt *direction)
// {
// 	direction->x = 0;
// 	direction->y = 0;
// 	if (cub->keys.a)
// 		direction->x -= SPEED * cub->display.delta_time;
// 	else if (cub->keys.d)
// 		direction->x += SPEED * cub->display.delta_time;
// 	if (cub->keys.s)
// 		direction->y += SPEED * cub->display.delta_time;
// 	else if (cub->keys.w)
// 		direction->y -= SPEED * cub->display.delta_time;
// }

void	init_direction(t_cub *cub, t_pt *direction)
{
	double	step;

	step = 0.01;
	direction->x = 0;
	direction->y = 0;
	if (cub->keys.w)
		direction->y -= step;
	else if (cub->keys.s)
		direction->y += step;
	if (cub->keys.a)
		direction->x -= step;
	else if (cub->keys.d)
		direction->x += step;
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



static int	is_wall(t_cub *cub, int x, int y)
{
	if (cub->map->pts[y][x].type)
	{
		if (cub->map->pts[y][x].type == '1')
		{
			printf("cub->map->pts[y=%d][x=%d].type == '1'\n", y, x);///////
			return (1);
		}
		if (cub->map->pts[y][x].type == 'D')
			return (1);
	}
	return (0);
}


int	too_close(double x, double y, int where)
{
	double	wand;
	double	dist;

	wand = 0.2;
	dist = 1;
	if (where == NORTH)
	{
		dist = y - floor(y);
		printf("where=[%d], dist=[%f]\n", where, dist);
	}
	else if (where == SOUTH)
	{
		dist = ceil(y) - y;
		printf("where=[%d], dist=[%f]\n", where, dist);
	}
	else if (where == WEST)
	{
		dist = x - floor(x);
		printf("where=[%d], dist=[%f]\n", where, dist);
	}
	else if (where == EAST)
	{
		dist = ceil(x) - x;
		printf("where=[%d], dist=[%f]\n", where, dist);
	}
	if (dist < wand)
	{
		printf("dist=[%f]\n\n", dist);
		return (1);
	}
	return (0);
}

/*Pour chacune des 4 directions
Si un mouvement se fait dans cette direction
Si une case plus loin dans cette direction on a un mur
Si la procimite a ce mur est inferieur a wand
Alors on annule le mouvement dans cette direction*/
void	check_edges(t_cub *cub, t_pt *direction)
{
	double	x;
	double	y;

	(void)direction;//
	x = cub->player.grid_pt.x;// + direction->x;
	y = cub->player.grid_pt.y;// + direction->y;
	printf("player position x=[%f] y=[%f]\n\n", x ,y);///
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

/*	printf("firection x=[%f] y=[%f]\n", direction.x, direction.y);///*/
void	move_player(t_cub *cub)
{
	t_pt	direction;

	init_direction(cub, &direction);
	printf("dx=[%f] dy=[%f]\n", direction.x, direction.y);//////
	rotate_direction(&direction, cub->player.player_angle);
	printf("dx=[%f] dy=[%f]\n", direction.x, direction.y);//////
	check_edges(cub, &direction);
	// printf("dx=[%f] dy=[%f]\n\n", direction.x, direction.y);//////

	double x = cub->player.grid_pt.x;// + direction->x;
	double y = cub->player.grid_pt.y;// + direction->y;
	printf("player position x=[%f] y=[%f]\n\n", x ,y);///

	cub->player.grid_pt.x += direction.x;
	cub->player.grid_pt.y += direction.y;
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}

// if
// - case au nord = wall
// - edge[0] <= wand
// - composante de mouvement vers le NORD
// alors
// annuler la composante de mvt vers le nord (y = 0)


// if (player too close to wall in y && player too close to wall in x)


// else if (player too close to wall in y)
// 	cub->player.grid_pt.x = direction.x;

// else if (player too close to wall in y)
// 	cub->player.grid_pt.x = direction.x;
// static int	is_wall(t_cub *cub, t_pt dest)
// {
// 	int	round_y;
// 	int	round_x;

// 	if (dest.x < 0 || dest.y < 0 || dest.x >= cub->map->width
// 		|| dest.y >= cub->map->height)
// 		return (1);
// 	round_y = (int)round(dest.y);
// 	round_x = (int)round(dest.x);
// 	if (cub->map->pts[round_y][round_x].type)
// 	{
// 		if (cub->map->pts[round_y][round_x].type == '1')
// 			return (1);
// 		if (cub->map->pts[round_y][round_x].type == 'D')
// 			return (1);
// 	}
// 	return (0);
// }
