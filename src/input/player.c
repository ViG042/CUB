/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:58:14 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 15:15:40 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	initialize_player(t_cub *cub)
{
	cub->offset_x = 1;
	cub->offset_y = 1;
	cub->player.player_pt.x = 200;
	cub->player.player_pt.y = 200;
	cub->player.cursor[TOP].x = cub->player.player_pt.x;
	cub->player.cursor[TOP].y = cub->player.player_pt.y - CURSOR_SIZE * 0.1;
	cub->player.cursor[LEFT].x = cub->player.player_pt.x - CURSOR_SIZE;
	cub->player.cursor[LEFT].y = cub->player.player_pt.y + CURSOR_SIZE;
	cub->player.cursor[RIGHT].x = cub->player.player_pt.x + CURSOR_SIZE;
	cub->player.cursor[RIGHT].y = cub->player.player_pt.y + CURSOR_SIZE;
}
