/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:20:56 by alex              #+#    #+#             */
/*   Updated: 2025/03/09 14:53:22 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	delta_ms = current_frame - cub->display.last_frame;
	cub->display.last_frame = current_frame;
	cub->display.delta_time = ((double)delta_ms) / 1000000.00;
}
