/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:31:02 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 13:36:41 by mkling           ###   ########.fr       */
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
		return (0);
	cub.w = 50;
	cub.h = 50;
	parse_file(&cub);
	init_window(&cub);
	project(&cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &handle_input_press, &cub);
	mlx_hook(cub.win, KeyRelease, KeyReleaseMask, &handle_input_release, &cub);
	mlx_hook(cub.win, DestroyNotify, LeaveWindowMask, &success_exit, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, (void *)&cub);
	mlx_loop(cub.mlx);
	wipe(&cub);
	return (0);
}
