/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:22:24 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 17:04:23 by mkling           ###   ########.fr       */
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

t_pt	turn_into_pts(char map_point, t_cub *cub)
{
	t_pt	point;

	point.y = cub->count / cub->map->width;
	point.x = fmod(cub->count, cub->map->width);
	point.type = map_point;
	if (map_point == '1' || map_point == ' ')
		point.z = 10;
	else if (map_point == '0')
		point.z = 0;
	else
		initialize_player(cub, &point);
	point.rgb = WHITE;
	// fprintf(stderr, "%c is pt x %f y %f z %f\n", map_point, point.x, point.y, point.z);
	return (point);
}

void	transform_map_into_pts(t_cub *cub)
{
	int		row;
	int		column;

	row = 0;
	column = 0;
	cub->map->pts_array = ft_calloc((cub->map->size) + 1, sizeof(t_pt));
	exit_if(!cub->map->pts_array, MALLOC_FAIL, cub);
	while (cub->map->clean_map[row])
	{
		column = 0;
		// fprintf(stderr, "row is %d column is %d, row string is %s\n", row, column, cub->map->clean_map[row]);
		while (cub->map->clean_map[row][column] != '\0')
		{
			cub->map->pts_array[cub->count]
				= turn_into_pts(cub->map->clean_map[row][column], cub);
			column++;
			cub->count++;
		}
		row++;
	}
	fprintf(stderr, "count is %d\n", cub->count);
}
