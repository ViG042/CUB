/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:01:24 by mkling            #+#    #+#             */
/*   Updated: 2025/03/03 18:01:40 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	write_syntax_error_message(int err_num)
{
	if (err_num == WRONG_ARG)
		ft_putstr_fd("Usage: <./cubd3d>   <map_name.ber>\n", 2);
	if (err_num == MAP_NAME)
		ft_putstr_fd("Wrong map name\n", 2);
	if (err_num == NO_PLAYER)
		ft_putstr_fd("We need one player\n", 2);
	if (err_num == TOO_BIG)
		ft_putstr_fd("This map is too big to be displayed on this screen\n", 2);
	if (err_num == NO_SPRITE)
		ft_putstr_fd("Couldn't load images\n", 2);
	if (err_num == NOT_RECT)
		ft_putstr_fd("Map is not a rectangle\n", 2);
	if (err_num == TOO_PLAYER)
		ft_putstr_fd("Too many players\n", 2);
	if (err_num == NOT_WALLED)
		ft_putstr_fd("We need walls all around the map\n", 2);
	if (err_num == UNKNOWN)
		ft_putstr_fd("Unknown character in the map\n", 2);
	if (err_num == EMPTY_LINE)
		ft_putstr_fd("There are empty lines in the map\n", 2);
}

void	write_error_message(int err_num)
{
	if (err_num == OPEN_FAIL)
		ft_putstr_fd("Problem opening the map file\n", 2);
	if (err_num == READ_FAIL)
		ft_putstr_fd("Problem reading the map file\n", 2);
	if (err_num == MALLOC_FAIL)
		ft_putstr_fd("Problem allocating memory\n", 2);
	if (err_num == MLX_INIT)
		ft_putstr_fd("Unable to intialize minilibX\n", 2);
	if (err_num == WIN_ALLOC)
		ft_putstr_fd("Unable to allocate a window\n", 2);
	if (err_num == IMG_ALLOC)
		ft_putstr_fd("Unable to allocate an image\n", 2);
	write_syntax_error_message(err_num);
}

void	exit_if(int condition, int err_num, t_cub *cub)
{
	if (condition == 0)
		return ;
	write_error_message(err_num);
	if (cub)
		wipe(cub);
	exit(1);
}

void	soft_exit_if(int condition, int err_num)
{
	if (condition == 0)
		return ;
	write_error_message(err_num);
	exit(1);
}
