/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:35:23 by mkling            #+#    #+#             */
/*   Updated: 2025/03/07 11:29:42 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
	{
		return (1);
	}
	return (0);
}

/*check for a line filled with spaces witch is not valid
check for a line with only valid map chacarters*/
int	is_valid_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	i = 0;
	while (str[i] && is_valid_char(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	get_clean_map_length(t_cub *cub)
{
	int	line;
	int	length;

	line = 0;
	length = 0;
	while (cub->map->array[line])
	{
		line++;
	}
	line--;
	while (is_valid_line(cub->map->array[line]) && line > 5)
	{
		length++;
		line--;
	}
	exit_if(!length, NO_MAP, cub);
	return (length);
}

void	fill_clean_map(t_cub *cub, int length)
{
	int	line;

	line = 0;
	while (cub->map->array[line])
	{
		line++;
	}
	line--;
	cub->map->clean_map[length] = NULL;
	length--;
	while (is_valid_line(cub->map->array[line]) && line > 5)
	{
		cub->map->clean_map[length] = cub->map->array[line];
		length--;
		line--;
	}
}

void	map_clean(t_cub *cub)
{
	int		length;

	length = get_clean_map_length(cub);
	cub->map->clean_map = ft_calloc(length + 1, sizeof(char *));
	exit_if(!cub->map->clean_map, MALLOC_FAIL, cub);
	fill_clean_map(cub, length);
}


