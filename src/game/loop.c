/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:20:40 by alex              #+#    #+#             */
/*   Updated: 2025/03/21 14:55:02 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotations(t_cub *cub)
{
	if (cub->keys.left)
		cub->player.player_angle -= ROT_SPEED * cub->display.delta_time;
	if (cub->keys.right)
		cub->player.player_angle += ROT_SPEED * cub->display.delta_time;
	if (cub->player.player_angle > 360)
		cub->player.player_angle = cub->player.player_angle / 360.00;
	if (cub->player.player_angle < -360)
		cub->player.player_angle = cub->player.player_angle / 360.00;
}

int	game_loop(void	*voidedcub)
{
	t_cub		*cub;

	cub = (t_cub *)voidedcub;
	if (cub->win == NULL)
		return (1);
	update_delta_time(cub);
	rotations(cub);
	move_player(cub);
	raycasting(cub);
	render(cub);
	return (0);
}
