/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:48:43 by vgodoy            #+#    #+#             */
/*   Updated: 2024/11/29 18:22:44 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_images3(t_var *v)
{
	v->e042 = mlx_xpm_file_to_image(v->mlx, "xpms/e042.xpm", &v->t, &v->t);
	if (!v->e042)
		return (destroy_img(v, 5), 0);
	v->e000 = mlx_xpm_file_to_image(v->mlx, "xpms/e000.xpm", &v->t, &v->t);
	if (!v->e000)
		return (destroy_img(v, 6), 0);
	v->e025 = mlx_xpm_file_to_image(v->mlx, "xpms/e025.xpm", &v->t, &v->t);
	if (!v->e025)
		return (destroy_img(v, 7), 0);
	v->e050 = mlx_xpm_file_to_image(v->mlx, "xpms/e050.xpm", &v->t, &v->t);
	if (!v->e050)
		return (destroy_img(v, 8), 0);
	v->e075 = mlx_xpm_file_to_image(v->mlx, "xpms/e075.xpm", &v->t, &v->t);
	if (!v->e075)
		return (destroy_img(v, 9), 0);
	v->e100 = mlx_xpm_file_to_image(v->mlx, "xpms/e100.xpm", &v->t, &v->t);
	if (!v->e100)
		return (destroy_img(v, 10), 0);
	v->e125 = mlx_xpm_file_to_image(v->mlx, "xpms/e125.xpm", &v->t, &v->t);
	if (!v->e125)
		return (destroy_img(v, 11), 0);
	return (1);
}

int	init_images2(t_var *v)
{
	v->bou1 = mlx_xpm_file_to_image(v->mlx, "xpms/bou1.xpm", &v->t, &v->t);
	if (!v->bou1)
		return (destroy_img(v, 12), 0);
	v->bou2 = mlx_xpm_file_to_image(v->mlx, "xpms/bou2.xpm", &v->t, &v->t);
	if (!v->bou2)
		return (destroy_img(v, 13), 0);
	v->bou3 = mlx_xpm_file_to_image(v->mlx, "xpms/bou3.xpm", &v->t, &v->t);
	if (!v->bou3)
		return (destroy_img(v, 14), 0);
	v->bou4 = mlx_xpm_file_to_image(v->mlx, "xpms/bou4.xpm", &v->t, &v->t);
	if (!v->bou4)
		return (destroy_img(v, 15), 0);
	return (1);
}

int	init_images1(t_var *v)
{
	v->wall = mlx_xpm_file_to_image(v->mlx, "xpms/wall.xpm", &v->t, &v->t);
	if (!v->wall)
		return (destroy_img(v, 1), 0);
	v->eaux = mlx_xpm_file_to_image(v->mlx, "xpms/eaux.xpm", &v->t, &v->t);
	if (!v->eaux)
		return (destroy_img(v, 2), 0);
	v->fire = mlx_xpm_file_to_image(v->mlx, "xpms/fire.xpm", &v->t, &v->t);
	if (!v->fire)
		return (destroy_img(v, 3), 0);
	v->coin = mlx_xpm_file_to_image(v->mlx, "xpms/coin.xpm", &v->t, &v->t);
	if (!v->coin)
		return (destroy_img(v, 4), 0);
	return (1);
}

int	init_images(t_var *v)
{
	if (!init_images1(v) || !init_images3(v) || !init_images2(v))
	{
		mlx_destroy_window(v->mlx, v->win);
		mlx_destroy_display(v->mlx);
		free(v->mlx);
		return (0);
	}
	return (1);
}
