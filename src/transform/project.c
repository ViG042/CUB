/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/06 22:56:15 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	project_minimap(t_cub *cub)
{
	int		index;
	int		minimap_offset;

	index = 0;
	minimap_offset = 20;
	cub->minimap = cub->map;
	while (index <= cub->map->size)
	{
		cub->minimap->pts_array[index].x *= 15;
		cub->minimap->pts_array[index].y *= 15;
		cub->minimap->pts_array[index].x += minimap_offset;
		cub->minimap->pts_array[index].y += minimap_offset;
		index++;
	}
	printf("index is %d\n", index);
}

void	project(t_cub *cub)
{
	project_minimap(cub);
}
