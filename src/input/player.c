/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:58:14 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 19:19:38 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	initialize_player(t_cub *cub, t_pt *start)
{
	cub->offset_x = 1;
	cub->offset_y = 1;
	cub->player.grid_pt = *start;
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
