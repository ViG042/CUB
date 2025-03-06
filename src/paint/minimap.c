/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:04:44 by mkling            #+#    #+#             */
/*   Updated: 2025/03/06 22:50:41 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	paint_miniplayer(t_cub *cub)
{
	cub->player.rgb = WHITE;
	paint_triangle(cub, &cub->player, WHITE);
}

void	paint_grid(t_cub *cub)
{
	int		index;
	t_pt	pt;

	index = 0;
	while (index <= cub->map->size)
	{
		pt = cub->minimap->pts_array[index];
		if (pt.type == '1')
			paint_square(cub, &pt, GREY);
		else
			paint_square(cub, &pt, BLACK);
		index++;
	}
}

void	paint_minimap(t_cub *cub)
{
	paint_grid(cub);
	paint_miniplayer(cub);
}
