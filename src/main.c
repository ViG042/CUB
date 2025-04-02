/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:31:02 by mkling            #+#    #+#             */
/*   Updated: 2025/04/02 10:24:54 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	check_arg_syntax(&cub, argc, argv);
	init_display(&cub);
	parse_file(&cub);
	init_minimap(cub.map);
	mlx_mouse_move(cub.mlx, cub.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_loop(cub.mlx);
	wipe(&cub);
	return (0);
}
