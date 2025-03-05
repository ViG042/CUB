/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:33:27 by mkling            #+#    #+#             */
/*   Updated: 2025/03/05 16:57:55 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	read_map_into_buffer(t_cub *cub)
{
	cub->fd = open(cub->map->name, O_RDONLY);
	soft_exit_if(cub->fd < 0, OPEN_FAIL);
	cub->map->size = read(cub->fd, cub->temp_map, MAX_TEMP_MAP - 1);
	soft_exit_if(cub->map->size < 0, READ_FAIL);
	cub->temp_map[cub->map->size] = '\0';
	soft_exit_if((read(cub->fd, cub->temp_map, 1) != 0), TOO_BIG);
}

void	process_elem(t_cub *cub)
{
	extract_elem(cub);

	//check_elem(cub);//check errors and all there
	//copy_map(cub);
	//check_map(cub);
	//exit_if(!check_walls(cub), NOT_RECT, cub);

	printf("extract elem done\n\n");//////

	printf("NO=[%s]", cub->elem->no);
//	printf("SO=[%s]", cub->elem->so);
//	printf("WE=[%s]", cub->elem->we);
//	printf("EA=[%s]", cub->elem->ea);
//	printf("F=[%s]", cub->elem->f);
//	printf("C=[%s]", cub->elem->c);
}

void	print_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s/n\n", array[i]);
		i++;
	}
	printf("\n");
}

void	parse_map(t_cub *cub)
{
	read_map_into_buffer(cub);
	cub->map->array = ft_split(cub->temp_map, '\n');
	exit_if(!cub->map->array, MALLOC_FAIL, cub);
	print_split(cub->map->array);////////
	process_elem(cub);
	/*
	init_angles_offsets(cub);
	transform_map_into_pts(cub);
	initialize_player(cub);
	*/
}
