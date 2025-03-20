/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:58:14 by mkling            #+#    #+#             */
/*   Updated: 2025/03/20 14:24:50 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	intialize_north_south(t_cub *cub, int type)
{
	if (type == 'N')
	{
		cub->player.deg_angle = 0.00;
		cub->player.dir.x = 0.00;
		cub->player.dir.y = 1.00;
		cub->player.plane.x = 0.66;
		cub->player.plane.y = 0.00;
	}
	else if (type == 'S')
	{
		cub->player.deg_angle = 180.00;
		cub->player.dir.x = 0.00;
		cub->player.dir.y = -1.00;
		cub->player.plane.x = -0.66;
		cub->player.plane.y = 0.00;
	}
}

static void	intialize_east_west(t_cub *cub, int type)
{
	if (type == 'E')
	{
		cub->player.deg_angle = 90.00;
		cub->player.dir.x = 1;
		cub->player.dir.y = 0;
		cub->player.plane.x = 0.00;
		cub->player.plane.y = 0.66;
	}
	else if (type == 'W')
	{
		cub->player.deg_angle = 270.00;
		cub->player.dir.x = -1;
		cub->player.dir.y = 0;
		cub->player.plane.x = 0.00;
		cub->player.plane.y = 0.66;
	}
}

void	initialize_player(t_cub *cub, t_pt *start)
{
	cub->offset_x = 0;//1;//
	cub->offset_y = 0;//1;
	cub->player.grid_pt = *start;
	intialize_north_south(cub, start->type);
	intialize_east_west(cub, start->type);
	printf("player direction is x[%f] and y[%f]\n", cub->player.dir.x, cub->player.dir.y);
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
