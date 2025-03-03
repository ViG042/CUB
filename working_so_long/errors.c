/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:53:25 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/03 11:37:33 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_maps(t_cub *v)
{
	int	y;

	y = 0;
	while (v->map[y])
	{
		free(v->map[y]);
		y++;
	}
	free(v->map);
	y = 0;
	while (v->map_copy[y])
	{
		free(v->map_copy[y]);
		y++;
	}
	free(v->map_copy);
}

int	basic_errors(int error)
{
	write (2, "Error\n", 7);
	if (error == 1)
		write (2, "Usage: <./so_long>   <map_name.ber>\n", 37);
	if (error == 2)
		write (2, "Problem opening the map file\n", 30);
	if (error == 3)
		write (2, "Problem reading the map file\n", 30);
	if (error == 4)
		write (2, "This file is too big to be displayed on this screen\n", 53);
	if (error == 5)
		write (2, "Problem spliting *temp_map to **map\n", 37);
	if (error == 6)
		write (2, "Wrong map name\n", 16);
	if (error == 7)
	{
		write (2, "two consecutives /n\n", 21);
		exit (0);
	}
	return (0);
}

int	errors(t_cub *v, int error)
{
	write (2, "Error\n", 7);
	if (error == 1)
		write (2, "We need one player\n", 20);
	if (error == 2)
		write (2, "This map is too big to be displayed on this screen\n", 52);
	if (error == 3)
		write (2, "Couldn't load images\n", 22);
	if (error == 4)
		write (2, "Map is not a rectagle\n", 23);
	if (error == 5)
		write (2, "Too many players\n", 18);
	if (error == 6)
		write (2, "We need at least one coin\n", 27);
	if (error == 7)
		write (2, "We need only one exit\n", 23);
	if (error == 8)
		write (2, "We need at least one reachable exit\n", 37);
	if (error == 9)
		write (2, "We need at least 100%/125% reachable coins\n", 44);
	if (error == 10)
		write (2, "We need walls all around\n", 26);
	if (error == 11)
		write (2, "Unknown char in the map\n", 25);
	free_maps(v);
	return (0);
}
