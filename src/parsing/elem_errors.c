/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:45:23 by vgodoy            #+#    #+#             */
/*   Updated: 2025/04/02 11:45:24 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	dbl_elem(int type, char *description)
{
	if (type)
	{
		if (description != NULL)
		{
			return (1);
		}
	}
	return (0);
}

int	elem_missing(t_cub *cub)
{
	int	i;

	i = NO;
	while (i <= C)
	{
		if (!(cub->elem[i].description))
			return (1);
		i++;
	}
	return (0);
}
