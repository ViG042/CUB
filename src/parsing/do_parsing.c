/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:33:27 by mkling            #+#    #+#             */
/*   Updated: 2025/03/07 11:30:01 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	fetch_info(t_cub *cub)
{
	cub->fd = open(cub->map->name, O_RDONLY);
	soft_exit_if(cub->fd < 0, OPEN_FAIL);
	cub->map->size = read(cub->fd, cub->temp_map, MAX_TEMP_MAP - 1);
	soft_exit_if(cub->map->size < 0, READ_FAIL);
	cub->temp_map[cub->map->size] = '\0';
	soft_exit_if((read(cub->fd, cub->temp_map, 1) != 0), TOO_BIG);
	cub->map->array = ft_split(cub->temp_map, '\n');
	exit_if(!cub->map->array, MALLOC_FAIL, cub);
}


void	parse_file(t_cub *cub)
{
	fetch_info(cub);
	print_info(cub->map->array);
	elem_extract(cub);
	print_elem(cub);
	elem_init(cub);
	print_init_elem(cub);
	map_clean(cub);
	print_map(cub->map->clean_map);
	map_check(cub);

	/*
	init_angles_offsets(cub);
	transform_map_into_pts(cub);
	initialize_player(cub);
	*/
}
