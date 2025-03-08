/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/07 17:38:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	project_minimap(t_cub *cub)
{
	int		index;

	index = 0;
	cub->minimap = cub->map;
	while (index <= cub->map->size)
	{
		cub->minimap->pts_array[index].x *= MINIMAP_SCALE;
		cub->minimap->pts_array[index].y *= MINIMAP_SCALE;
		cub->minimap->pts_array[index].x += MINIMAP_OFFSET;
		cub->minimap->pts_array[index].y += MINIMAP_OFFSET;
		index++;
	}
	printf("index is %d\n", index);
}

void	project(t_cub *cub)
{
	project_minimap(cub);
}
