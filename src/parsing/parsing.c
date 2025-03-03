/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:33:27 by mkling            #+#    #+#             */
/*   Updated: 2025/03/03 18:59:07 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	read_map_into_buffer(t_cub *cub)
{
	cub->fd = open(cub->map->name, O_RDONLY);
	soft_exit_if(cub->fd < 0, OPEN_FAIL);
	cub->map->size = read(cub->fd, cub->temp_map, 1020);
	soft_exit_if(cub->map->size < 0, READ_FAIL);
	cub->temp_map[cub->map->size] = '\0';
	soft_exit_if((read(cub->fd, cub->temp_map, 1) != 0), TOO_BIG);
}

void	parse_map(t_cub *cub)
{
	read_map_into_buffer(cub);
	cub->map->split_by_line = ft_split(cub->temp_map, '\n');
	exit_if(!cub->map->split_by_line, MALLOC_FAIL, cub);
	cub->map->array = ft_split(cub->temp_map, '\n');
	exit_if(!cub->map->array, MALLOC_FAIL, cub);
	check_map_syntax(cub);
	initialize_player(cub);
}
