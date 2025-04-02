/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:39 by mkling            #+#    #+#             */
/*   Updated: 2025/04/02 11:56:31 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_red(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_green(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_blue(int color)
{
	return (color & 0xFF);
}

int	encode_rgb(t_byte red, t_byte green, t_byte blue)
{
	return (red << 16 | green << 8 | blue);
}
