/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:20:40 by alex              #+#    #+#             */
/*   Updated: 2025/03/20 14:25:46 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*	// 	printf("player grid pt is %f, %f - ", cub->player.grid_pt.x, cub->player.grid_pt.y);
	// 	printf("map grid pt is %f, %f\n", cub->player.map_pt.x, cub->player.map_pt.y);*/
static void	rotations(t_cub *cub)
{
	t_pt	dir;
	t_pt	plane;

	dir = cub->player.dir;
	plane = cub->player.plane;
	if (cub->keys.left)
	{
		printf("rotating left\n");
		cub->player.deg_angle -= SPEED * 100 * cub->display.delta_time;
		cub->player.dir.x = dir.x * cos(-ROTSPEED) - dir.y * sin(-ROTSPEED);
		cub->player.dir.y = dir.x * sin(-ROTSPEED) + dir.y * cos(-ROTSPEED);
		cub->player.plane.x = plane.x * cos(-ROTSPEED) - plane.y * sin(-ROTSPEED);
		cub->player.plane.y = plane.x * sin(-ROTSPEED) + plane.y * cos(-ROTSPEED);
	}
	if (cub->keys.right)
	{
		printf("rotating right\n");
		cub->player.deg_angle += SPEED * 100 * cub->display.delta_time;
		cub->player.dir.x = dir.x * cos(ROTSPEED) - dir.y * sin(ROTSPEED);
		cub->player.dir.y = dir.x * sin(ROTSPEED) + dir.y * cos(ROTSPEED);
		cub->player.plane.x = plane.x * cos(ROTSPEED) - plane.y * sin(ROTSPEED);
		cub->player.plane.y = plane.x * sin(ROTSPEED) + plane.y * cos(ROTSPEED);
	}
	if (cub->player.deg_angle > 360)
		cub->player.deg_angle = cub->player.deg_angle / 360.00;
	if (cub->player.deg_angle < -360)
		cub->player.deg_angle = cub->player.deg_angle / 360.00;
	printf("player is dir x[%f] y[%f]\n", cub->player.dir.x, cub->player.dir.y);
}

int	game_loop(void	*voidedcub)
{
	t_cub		*cub;

	cub = (t_cub *)voidedcub;

	if (cub->win == NULL)
		return (1);
	update_delta_time(cub);
	cub->display.counter += cub->display.delta_time;
	if (cub->display.counter > 1)
	{
		cub->display.fps = 1.0 / cub->display.delta_time;
		cub->display.counter = 0;
	}
	rotations(cub);
	move_player(cub);
	paint_background(&cub->img, BLACK);
	raycasting(cub);
	render(cub);
	return (0);
}
