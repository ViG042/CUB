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

void	init_image_address(t_img *img)
{
	img->address = mlx_get_data_addr(img->mlx_img, &img->bit_per_pixel,
			&img->line_len, &img->endian);
}

void	init_image(t_cub *cub, t_img *img)
{
	img->mlx_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	exit_if(!img->mlx_img, IMG_ALLOC, cub);
	init_image_address(img);
}

void	init_window(t_cub *cub)
{
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	exit_if((!cub->win), WIN_ALLOC, cub);
	cub->display.fps = 0.00;
	cub->display.counter = 0;
}

void	init_display(t_cub *cub)
{
	cub->mlx = mlx_init();
	exit_if(!cub->mlx, MALLOC_FAIL, cub);
	init_window(cub);
	init_image(cub, &cub->img);
	init_image(cub, &cub->minimap);
	init_image(cub, &cub->hud);
	mlx_hook(cub->win, KeyPress, KeyPressMask, &handle_input_press, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, &handle_input_release, cub);
	mlx_hook(cub->win, DestroyNotify, LeaveWindowMask, &success_exit, cub);
	// move_player(cub);
	mlx_loop_hook(cub->mlx, &game_loop, (void *)cub);
}

int	is_in_window(int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x > WIN_WIDTH || y > WIN_HEIGHT)
		return (0);
	return (1);
}
