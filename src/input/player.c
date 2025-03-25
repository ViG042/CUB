/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:58:14 by mkling            #+#    #+#             */
/*   Updated: 2025/03/25 11:38:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	initialize_player(t_cub *cub, t_pt *start)
{
	cub->player.offset_x = 0;
	cub->player.offset_y = 0;
	cub->player.grid_pt.x = start->x + 0.5;
	cub->player.grid_pt.y = start->y + 0.5;
	// cub->player.grid_pt = *start;
	if (start->type == 'N')
		cub->player.player_angle = 0.00;
	if (start->type == 'E')
		cub->player.player_angle = 90.00;
	if (start->type == 'S')
		cub->player.player_angle = 180.00;
	if (start->type == 'W')
		cub->player.player_angle = 270.00;
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
