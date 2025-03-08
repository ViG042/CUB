/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:31:02 by mkling            #+#    #+#             */
/*   Updated: 2025/03/08 23:25:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotations(t_cub *cub)
{
	if (cub->keys.left)
		cub->player_angle -= 5;
	if (cub->keys.right)
		cub->player_angle += 5;
}

static void	rotate_direction(t_pt *point, float angle)
{
	float	radian;
	float	cos_angle;
	float	sin_angle;
	t_pt	rotated;

	radian = angle * RADIAN;
	cos_angle = cos(radian);
	sin_angle = sin(radian);
	rotated.x = cos_angle * point->x - sin_angle * point->y;
	rotated.y = sin_angle * point->x + cos_angle * point->y;
	point->x = rotated.x;
	point->y = rotated.y;
}

static void	movements(t_cub *cub)
{
	t_pt	direction;

	direction.x = 0;
	direction.y = 0;
	if (cub->keys.a)
		direction.x -= 5;
	if (cub->keys.d)
		direction.x += 5;
	if (cub->keys.s)
		direction.y += 5;
	if (cub->keys.w)
		direction.y -= 5;

	rotate_direction(&direction, cub->player_angle);
	cub->player.x += direction.x;
	cub->player.y += direction.y;
}

int	game_loop(void	*voidedcub)
{
	t_cub		*cub;
	static int	i = 0;

	cub = (t_cub *)voidedcub;
	if (cub->win == NULL)
		return (1);
	rotations(cub);
	movements(cub);
	render(cub);
	printf("frame %d\n", i++);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	check_arg_syntax(&cub, argc, argv);
	parse_map(&cub);
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
