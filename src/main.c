/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:31:02 by mkling            #+#    #+#             */
/*   Updated: 2025/03/06 17:18:34 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	check_arg_syntax(&cub, argc, argv);
	cub.mlx = mlx_init();
	if (!cub.mlx)
		return (0);///////ameliorer erreur
	cub.w = 50;
	cub.h = 50;
	parse_file(&cub);
	init_window(&cub);
	mlx_loop_hook(cub.mlx, NULL, &cub);
	render(&cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &handle_input, &cub);
	mlx_hook(cub.win, DestroyNotify, LeaveWindowMask, &success_exit, &cub);
	mlx_mouse_hook(cub.win, &handle_mouse, &cub);
	mlx_loop(cub.mlx);
	wipe(&cub);
	return (0);
}
