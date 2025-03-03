/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:36:13 by mkling            #+#    #+#             */
/*   Updated: 2025/03/03 14:07:24 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"



void	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	exit_if(!cub->mlx, MLX_INIT, cub);
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	exit_if((!cub->win), WIN_ALLOC, cub);
	cub->img.mlx_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	exit_if(!cub->img.mlx_img, IMG_ALLOC, cub);
	cub->img.address = mlx_get_data_addr(cub->img.mlx_img,
			&cub->img.bit_per_pixel, &cub->img.line_len,
			&cub->img.endian);
	render(cub);
}
