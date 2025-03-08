/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:31:02 by mkling            #+#    #+#             */
/*   Updated: 2025/03/09 00:06:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	rotations(t_cub *cub)
{
	if (cub->keys.left)
		cub->player_angle -= SPEED * cub->delta_time;
	if (cub->keys.right)
		cub->player_angle += SPEED * cub->delta_time;
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
		direction.x -= SPEED * cub->delta_time;
	if (cub->keys.d)
		direction.x += SPEED * cub->delta_time;
	if (cub->keys.s)
		direction.y += SPEED * cub->delta_time;
	if (cub->keys.w)
		direction.y -= SPEED * cub->delta_time;

	rotate_direction(&direction, cub->player_angle);
	cub->player.x += direction.x;
	cub->player.y += direction.y;
}

long long	get_microseconds(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_usec + time.tv_sec * 1000000);
}

void	update_delta_time(t_cub *cub)
{
	long long	current_frame;
	long long	delta_ms;

	current_frame = get_microseconds();
	delta_ms = current_frame - cub->last_frame;
	cub->last_frame = current_frame;
	cub->delta_time = ((double)delta_ms) / 1000000.00;
}

int	game_loop(void	*voidedcub)
{
	t_cub		*cub;
	static float counter = 0;

	cub = (t_cub *)voidedcub;
	if (cub->win == NULL)
		return (1);
	update_delta_time(cub);
	counter += cub->delta_time;
	if (counter > 1)
	{
		cub->fps = 1.0 / cub->delta_time;
		printf("FPS: %f\n", cub->fps);
		counter = 0;
	}
	rotations(cub);
	movements(cub);
	render(cub);
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
