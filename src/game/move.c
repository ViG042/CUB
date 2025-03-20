/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:25 by mkling            #+#    #+#             */
/*   Updated: 2025/03/20 14:46:22 by mkling           ###   ########.fr       */
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

void	init_destination(t_cub *cub, t_pt *destination)
{
	double	step;

	step = 0.01;
	destination->x = 0;
	destination->y = 0;
	if (cub->keys.w)
		destination->y = -(cub->player.dir.y * SPEED);
	else if (cub->keys.s)
		destination->y = cub->player.dir.y * SPEED;
	if (cub->keys.a)
		destination->x = cub->player.dir.x * SPEED;
	else if (cub->keys.d)
		destination->x = -(cub->player.dir.x * SPEED);
	printf("player x[%f]y[%f] destination is x[%f] and y[%f]\n", cub->player.map_pt.x, cub->player.map_pt.y, destination->x, destination->y);
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

/*	double x = cub->player.grid_pt.x;
	double y = cub->player.grid_pt.y;
	printf("firection x=[%f] y=[%f]\n", direction.x, direction.y);
	printf("dx=[%f] dy=[%f]\n", direction.x, direction.y);/////////
		printf("player position x=[%f] y=[%f]\n\n", x ,y);///*/
void	move_player(t_cub *cub)
{
	t_pt	destination;

	init_destination(cub, &destination);
	check_edges(cub, &destination);
	cub->player.grid_pt.x += destination.x;
	cub->player.grid_pt.y += destination.y;
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
	printf("player map is x[%f] and y[%f]\n", cub->player.map_pt.x, cub->player.map_pt.y);
}
