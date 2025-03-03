/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:16:39 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/03 11:37:33 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	destroy_img_2(t_cub *v, int failed_img)
{
	if (failed_img > 8)
		mlx_destroy_image(v->mlx, v->e050);
	if (failed_img > 9)
		mlx_destroy_image(v->mlx, v->e075);
	if (failed_img > 10)
		mlx_destroy_image(v->mlx, v->e100);
	if (failed_img > 11)
		mlx_destroy_image(v->mlx, v->e125);
	if (failed_img > 12)
		mlx_destroy_image(v->mlx, v->bou1);
	if (failed_img > 13)
		mlx_destroy_image(v->mlx, v->bou2);
	if (failed_img > 14)
		mlx_destroy_image(v->mlx, v->bou3);
	if (failed_img > 15)
		mlx_destroy_image(v->mlx, v->bou4);
}

void	destroy_img(t_cub *v, int failed_img)
{
	if (failed_img > 1)
		mlx_destroy_image(v->mlx, v->wall);
	if (failed_img > 2)
		mlx_destroy_image(v->mlx, v->eaux);
	if (failed_img > 3)
		mlx_destroy_image(v->mlx, v->coin);
	if (failed_img > 4)
		mlx_destroy_image(v->mlx, v->fire);
	if (failed_img > 5)
		mlx_destroy_image(v->mlx, v->e042);
	if (failed_img > 6)
		mlx_destroy_image(v->mlx, v->e000);
	if (failed_img > 7)
		mlx_destroy_image(v->mlx, v->e025);
	destroy_img_2(v, failed_img);
}
