/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:20:40 by alex              #+#    #+#             */
/*   Updated: 2025/03/10 16:59:53 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotations(t_cub *cub)
{
	if (cub->keys.left)
		cub->player.player_angle -= SPEED * 100 * cub->display.delta_time;
	if (cub->keys.right)
		cub->player.player_angle += SPEED * 100 * cub->display.delta_time;
	if (cub->player.player_angle > 360)
		cub->player.player_angle = cub->player.player_angle / 360.00;
	if (cub->player.player_angle < -360)
		cub->player.player_angle = cub->player.player_angle / 360.00;
}

int	game_loop(void	*voidedcub)
{
	t_cub		*cub;
	static float counter = 0;

	cub = (t_cub *)voidedcub;
	if (cub->win == NULL)
		return (1);
	update_delta_time(cub);
	counter += cub->display.delta_time;
	if (counter > 1)
	{
		cub->display.fps = 1.0 / cub->display.delta_time;
		counter = 0;
	}
	rotations(cub);
	move_player(cub);
	render(cub);
	return (0);
}
