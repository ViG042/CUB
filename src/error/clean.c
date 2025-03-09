/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:07:08 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 16:45:44 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_elem(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (cub->elem[i].description)
			free(cub->elem[i].description);
		i++;
	}
}

static void	free_map(t_map *map)
{
	if (map->array)
		ft_free_tab(map->array);
	// if (map->clean_map)
	// 	ft_free_tab(map->clean_map);
	free(map->pts_array);
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
