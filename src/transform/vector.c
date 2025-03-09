/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:22:24 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 18:00:25 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_angles_offsets(t_cub *cub)
{
	cub->offset_x = WIN_WIDTH / 2;
	cub->offset_y = WIN_HEIGHT / 2;
	cub->unit = 10.0;
	cub->zoom = 10.0;
	cub->player.player_angle = 0;
}

t_pt	turn_into_pts(t_cub *cub, int row, int column)
{
	t_pt	point;

	point.y = row;
	point.x = column;
	point.type = cub->map->clean_map[row][column];
	if (point.type == 'W' || point.type == 'E'
		|| point.type == 'N' || point.type == 'S')
		initialize_player(cub, &point);
	point.rgb = WHITE;
	return (point);
}

void	transform_map_into_pts(t_cub *cub)
{
	int		row;
	int		column;

	row = 0;
	cub->map->pts_array = ft_calloc((cub->map->size) + 1, sizeof(t_pt));
	exit_if(!cub->map->pts_array, MALLOC_FAIL, cub);
	while (cub->map->clean_map[row])
	{
		column = 0;
		while (cub->map->clean_map[row][column] != '\0')
		{
			cub->map->pts_array[cub->map->pt_count]
				= turn_into_pts(cub, row, column);
			column++;
			cub->map->pt_count++;
		}
		row++;
	}
}
