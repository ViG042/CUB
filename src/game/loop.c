/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:20:40 by alex              #+#    #+#             */
/*   Updated: 2025/04/02 10:21:29 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	open_close_if_door(t_cub *cub, t_tile *tile, const t_pt *player)
{
	t_pt	door_mid;

	if (tile->type != DOOR)
		return ;
	door_mid.x = tile->x + 0.5;
	door_mid.y = tile->y + 0.5;
	if ((player->x >= door_mid.x - 1.5 && player->x <= door_mid.x + 1.5)
		&& (player->y >= door_mid.y - 1.5 && player->y <= door_mid.y + 1.5))
		tile->state += 1 * cub->display.delta_time;
	else
		tile->state -= 1 * cub->display.delta_time;
	tile->state = fclamp(tile->state, 0, 1);
}

void	update_tiles(t_cub *cub)
{
	int		y;
	int		x;

	x = 0;
	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < cub->map->width)
		{
			open_close_if_door(cub, &cub->map->tiles[y][x],
				&cub->player.grid_pt);
			x++;
		}
		y++;
	}
}

static void	rotations(t_cub *cub)
{
	float	mouse_from_center;
	float	middle_of_window;

	if (cub->keys.left)
		cub->player.angle -= ROT_SPEED * cub->display.delta_time;
	if (cub->keys.right)
		cub->player.angle += ROT_SPEED * cub->display.delta_time;
	middle_of_window = WIN_WIDTH / 2;
	mouse_from_center = middle_of_window - cub->keys.mouse_x;
	mouse_from_center = mouse_from_center / middle_of_window;
	cub->player.angle -= mouse_from_center * ROT_SPEED
		* cub->display.delta_time;
	if (cub->player.angle > 360)
		cub->player.angle = cub->player.angle / 360.00;
	if (cub->player.angle < -360)
		cub->player.angle = cub->player.angle / 360.00;
}

int	game_loop(void	*voidedcub)
{
	t_cub		*cub;

	cub = (t_cub *)voidedcub;
	if (cub->win == NULL)
		return (1);
	update_delta_time(cub);
	update_tiles(cub);
	rotations(cub);
	move_player(cub);
	raycasting(cub);
	render(cub);
	return (0);
}
