/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:44:35 by vgodoy            #+#    #+#             */
/*   Updated: 2025/04/02 11:46:38 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_angles_offsets(t_cub *cub)
{
	cub->player.angle = 0;
}

static void	set_width_and_height(t_cub *cub)
{
	int	height;
	int	width;
	int	tile_count;
	int	line_len;

	height = 0;
	width = 0;
	tile_count = 0;
	while (cub->map->clean_map[height])
	{
		line_len = ft_strlen(cub->map->clean_map[height]);
		tile_count += line_len;
		if (line_len > width)
			width = line_len;
		height++;
	}
	cub->map->height = height;
	cub->map->width = width;
	cub->map->size = tile_count;
}

static void	fetch_info(t_cub *cub)
{
	int	fd;

	fd = open(cub->map->name, O_RDONLY);
	soft_exit_if(fd < 0, OPEN_FAIL);
	cub->map->size = read(fd, cub->temp_map, MAX_TEMP_MAP - 1);
	soft_exit_if(cub->map->size < 0, READ_FAIL);
	cub->temp_map[cub->map->size] = '\0';
	soft_exit_if((read(fd, cub->temp_map, 1) != 0), TOO_BIG);
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
	printf("\n🚀 Map has been cleaned !\n\n");
	map_check(cub);
	set_width_and_height(cub);
	init_angles_offsets(cub);
	transform_map_into_tiles(cub);
}
