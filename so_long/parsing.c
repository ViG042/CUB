/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:26:22 by vgodoy            #+#    #+#             */
/*   Updated: 2024/11/29 18:34:58 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	configuration(t_var *v)
{
	if (!check_walls(v))
		return (errors(v, 10));
	if (v->i_player == 0)
		return (errors(v, 1));
	if (v->i_player > 1)
		return (errors(v, 5));
	if (v->i_coin < 1)
		return (errors(v, 6));
	if (v->i_exit != 1)
		return (errors(v, 7));
	return (1);
}

int	get_temp_map(t_var *v)
{
	int	map_size;

	v->fd = open(v->map_name, O_RDONLY);
	if (v->fd < 0)
		return (basic_errors(2));
	map_size = read(v->fd, v->temp_map, 1020);
	if (map_size < 0)
		return (basic_errors(3));
	v->temp_map[map_size] = '\0';
	if (read(v->fd, v->temp_map, 1) != 0)
		return (basic_errors(4));
	return (1);
}

int	parsing(t_var *v)
{
	if (!get_temp_map(v))
		return (0);
	v->map = ft_split(v->temp_map, '\n');
	if (!v->map)
		return (basic_errors(4));
	v->map_copy = ft_split(v->temp_map, '\n');
	if (!v->map_copy)
		return (basic_errors(4));
	if (!get_width_and_height(v))
		return (0);
	if (!configuration(v))
		return (0);
	if (!start_flood_fill(v))
		return (0);
	return (1);
}
