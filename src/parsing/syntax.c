/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:54:23 by mkling            #+#    #+#             */
/*   Updated: 2025/03/06 22:39:17 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	check_filename_syntax(char *map_filepath)
{
	int	fd_len;
	int	fd;

	fd_len = ft_strlen(map_filepath);
	soft_exit_if(fd_len < 4, MAP_NAME);
	soft_exit_if((ft_strcmp(&map_filepath[fd_len - 4], ".cub") != 0), MAP_NAME);
	fd = open(map_filepath, O_RDONLY);
	soft_exit_if(fd < 0, OPEN_FAIL);
	close(fd);
}

void	check_arg_syntax(t_cub *cub, int argc, char **argv)
{
	soft_exit_if(argc != 2, WRONG_ARG);
	soft_exit_if(argv[1][0] == '\0', WRONG_ARG);
	check_filename_syntax(argv[1]);
	cub->map = ft_calloc(sizeof(t_map), 1);
	cub->minimap = ft_calloc(sizeof(t_map), 1);
	cub->map->name = argv[1];
}
