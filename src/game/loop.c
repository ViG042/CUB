/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:20:40 by alex              #+#    #+#             */
/*   Updated: 2025/03/31 17:30:40 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	open_close_if_door(t_cub *cub, t_tile *tile, const t_pt *player)
{
	float	door_center_x;
	float	door_center_y;

	if (tile->type != DOOR)
		return ;
	door_center_x = tile->x + 0.5;
	door_center_y = tile->y + 0.5;
	if ((player->x >= door_center_x - 1.5 && player->x <= door_center_x + 1.5)
		&& (player->y >= door_center_y - 1.5 && player->y <= door_center_y + 1.5))
		tile->state += 1 * cub->display.delta;
	else
		tile->state -= 1 * cub->display.delta;
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
			open_close_if_door(cub, &cub->map->tiles[y][x], &cub->player.grid_pt);
			x++;
		}
		y++;
	}
}

// static void	rotate_player(t_play *player, t_key *keys, float delta)
// {
// 	if (keys->left)
// 		player->deg_angle -= ROT_SPEED * delta;
// 	if (keys->right)
// 		player->deg_angle += ROT_SPEED * delta;
// 	// if (keys->mouse_x > cub->display.mid_x + 30)
// 	// 	cub->player->deg_angle -= ROT_SPEED * delta;
// 	// if (keys->mouse_x < cub->display.mid_x - 30)
// 	// 	cub->player->deg_angle += ROT_SPEED * delta;
// 	if (player->deg_angle > 360)
// 		player->deg_angle = player->deg_angle / 360.00;
// 	if (player->deg_angle < -360)
// 		player->deg_angle = player->deg_angle / 360.00;
// }

static void	rotate_player(t_play *player, t_key *keys, float delta)
{
	float	old_dir_x;
	float	old_plane_x;

	if (keys->left)
	{
		player->deg_angle -= ROT_SPEED * delta;
		old_dir_x = player->dir.x;
		player->dir.x = player->dir.x * cos(ROT_SPEED) - player->dir.y * sin(ROT_SPEED);
		player->dir.y = old_dir_x * sin(ROT_SPEED) + player->dir.y * cos(ROT_SPEED);
		old_plane_x = player->plane.x;
		player->plane.x = player->plane.x * cos(ROT_SPEED) - player->plane.y * sin(ROT_SPEED);
		player->plane.y = old_plane_x * sin(ROT_SPEED) + player->plane.y * cos(ROT_SPEED);
	}
	if (keys->right)
	{
		player->deg_angle += ROT_SPEED * delta;
		old_dir_x = player->dir.x;
		player->dir.x = player->dir.x * cos(-ROT_SPEED) - player->dir.y * sin(-ROT_SPEED);
		player->dir.y = old_dir_x * sin(-ROT_SPEED) + player->dir.y * cos(-ROT_SPEED);
		old_plane_x = player->plane.x;
		player->plane.x = player->plane.x * cos(-ROT_SPEED) - player->plane.y * sin(-ROT_SPEED);
		player->plane.y = old_plane_x * sin(-ROT_SPEED) + player->plane.y * cos(-ROT_SPEED);
	}
}

int	game_loop(void	*voidedcub)
{
	t_cub		*cub;

	cub = (t_cub *)voidedcub;
	if (cub->win == NULL)
		return (1);
	update_delta(cub);
	update_tiles(cub);
	rotate_player(&cub->player, &cub->keys, cub->display.delta);
	move_player(&cub->player, &cub->keys, cub->map, cub->display.delta);
	raycasting(cub);
	render(cub);
	return (0);
}
