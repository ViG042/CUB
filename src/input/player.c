/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:58:14 by mkling            #+#    #+#             */
/*   Updated: 2025/03/30 21:11:37 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	initialize_player(t_cub *cub, float x, float y, int orientation)
{
	cub->player.offset_x = 0;
	cub->player.offset_y = 0;
	cub->player.grid_pt.x = x + 0.5;
	cub->player.grid_pt.y = y + 0.5;
	if (orientation == 'N')
		cub->player.player_angle = 0.00;
	if (orientation == 'E')
		cub->player.player_angle = 90.00;
	if (orientation == 'S')
		cub->player.player_angle = 180.00;
	if (orientation == 'W')
		cub->player.player_angle = 270.00;
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
