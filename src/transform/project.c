/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:47:28 by mkling            #+#    #+#             */
/*   Updated: 2025/03/10 15:47:00 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_pt	project_point(t_cub	*cub, t_pt pt)
{
	(void)cub;
	pt.x *= MINIMAP_SCALE;
	pt.y *= MINIMAP_SCALE;
	pt.x += MINIMAP_OFFSET - MINIMAP_TILE_SIZE / 2;
	pt.y += MINIMAP_OFFSET - MINIMAP_TILE_SIZE / 2;
	return (pt);
}

void	project(t_cub *cub)
{
	cub->player.map_pt = project_point(cub, cub->player.grid_pt);
}
