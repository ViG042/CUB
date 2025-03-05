/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:07:08 by mkling            #+#    #+#             */
/*   Updated: 2025/03/05 18:43:59 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_elem(t_cub *cub)
{
	if (cub->elem.no)
		free(cub->elem.no);
	if (cub->elem.so)
		free(cub->elem.so);
	if (cub->elem.we)
		free(cub->elem.we);
	if (cub->elem.ea)
		free(cub->elem.ea);
	if (cub->elem.f)
		free(cub->elem.f);
	if (cub->elem.c)
		free(cub->elem.c);
	if (cub->elem.d)
		free(cub->elem.d);
}

static void	free_map(t_map *map)
{
	free(map->array);
	free(map);
}

int	success_exit(t_cub *cub)
{
	wipe(cub);
	exit(0);
	return (0);
}

void	wipe(t_cub *cub)
{
	if (cub->map)
	{
		if (cub->img.mlx_img)
			mlx_destroy_image(cub->mlx, cub->img.mlx_img);
		free_map(cub->map);
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	free_elem(cub);
}
