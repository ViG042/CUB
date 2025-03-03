/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:16:39 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/03 11:37:33 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	close_window(t_cub *v, int success)
{
	if (success == 1)
		write(1, "You win !\n", 11);
	else if (success == 2)
		write(1, "You lose...\n", 13);
	destroy_img(v, 16);
	mlx_destroy_window(v->mlx, v->win);
	mlx_destroy_display(v->mlx);
	free(v->mlx);
	free_maps(v);
	exit(0);
}

int	key_press(int keycode, t_cub *v)
{
	if (keycode == 65307)
		close_window(v, 0);
	if (keycode == 'd' && v->map[v->p_y][v->p_x + 1] != '1')
		v->new_x += 1;
	if (keycode == 'a' && v->map[v->p_y][v->p_x - 1] != '1')
		v->new_x -= 1;
	if (keycode == 'w' && v->map[v->p_y - 1][v->p_x] != '1')
		v->new_y -= 1;
	if (keycode == 's' && v->map[v->p_y + 1][v->p_x] != '1')
		v->new_y += 1;
	return (0);
}

int	update(t_cub *v)
{
	move(v);
	if (v->i_boue < 400)
		v->i_boue++;
	else
		v->i_boue = 1;
	v->itoa1 = ft_itoa(v->mvt);
	v->itoa2 = ft_itoa(v->i_coin);
	v->itoa3 = ft_itoa(v->i_life);
	show_map(v);
	mlx_string_put(v->mlx, v->win, 5, 20, 0xFFFFFF, "Compteur");
	mlx_string_put(v->mlx, v->win, 25, 40, 0xFFFFFF, v->itoa1);
	mlx_string_put(v->mlx, v->win, 15, 70, 0xFFFFFF, "Coins");
	mlx_string_put(v->mlx, v->win, 25, 90, 0xFFFFFF, v->itoa2);
	mlx_string_put(v->mlx, v->win, 65, 20, 0xFFFFFF, "Lifes");
	mlx_string_put(v->mlx, v->win, 75, 40, 0xFFFFFF, v->itoa3);
	free(v->itoa1);
	free(v->itoa2);
	free(v->itoa3);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	v;

	if (argc != 2)
		return (basic_errors(1));
	if (!initialisations(&v, argv[1]))
		return (-1);
	if (!parsing(&v))
		return (-1);
	v.mlx = mlx_init();
	if (!v.mlx)
		return (0);
	v.win = mlx_new_window(v.mlx, v.x_len * 50, v.y_len * 50, "so_long");
	if (!v.win)
		return (0);
	if (!init_images(&v))
		return (errors(&v, 3), -1);
	mlx_key_hook(v.win, key_press, &v);
	mlx_hook(v.win, 17, 0, close_window, &v);
	mlx_loop_hook(v.mlx, update, &v);
	mlx_loop(v.mlx);
	return (0);
}
