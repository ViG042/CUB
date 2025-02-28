/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:48:43 by vgodoy            #+#    #+#             */
/*   Updated: 2024/11/29 17:54:49 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	map_name(t_var *v)
{
	int	i;

	i = 0;
	while (v->map_name[i])
		i++;
	if (i < 5)
		return (0);
	if (v->map_name[i -1] != 'r'
		|| v->map_name[i - 2] != 'e'
		|| v->map_name[i - 3] != 'b'
		|| v->map_name[i - 4] != '.')
		return (0);
	return (1);
}

int	initialisations(t_var *v, char *name)
{
	v->map_name = name;
	if (!map_name(v))
		return (basic_errors(6));
	v->t = 50;
	v->mvt = 0;
	v->i_boue = 0;
	v->i_coin = 0;
	v->i_life = 1;
	v->i_player = 0;
	v->i_exit = 0;
	v->i_exit_copy = 0;
	v->i_coin_copy = 0;
	v->i_coin_reach = 0;
	return (1);
}
