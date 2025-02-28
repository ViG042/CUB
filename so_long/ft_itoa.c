/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:51:35 by vgodoy            #+#    #+#             */
/*   Updated: 2024/05/15 16:54:56 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	s_n_length(int n)
{
	int	n_length;

	n_length = 1;
	if (n < 0)
		n_length++;
	while (n != 0)
	{
		n_length++;
		n = n / 10;
	}
	return (n_length);
}

static char	*s_zero(void)
{
	char	*zero;

	zero = malloc(2);
	if (!zero)
		return (NULL);
	zero[0] = '0';
	zero[1] = '\0';
	return (zero);
}

static char	*s_intmin(void)
{
	char	*intmin;

	intmin = malloc(12);
	if (!intmin)
		return (NULL);
	intmin[0] = '-';
	intmin[1] = '2';
	intmin[2] = '1';
	intmin[3] = '4';
	intmin[4] = '7';
	intmin[5] = '4';
	intmin[6] = '8';
	intmin[7] = '3';
	intmin[8] = '6';
	intmin[9] = '4';
	intmin[10] = '8';
	intmin[11] = '\0';
	return (intmin);
}

static char	*s_itoa(int size, int n)
{
	char	*itoa;

	itoa = malloc(size);
	if (!itoa)
		return (NULL);
	if (n < 0)
		itoa[0] = '-';
	size--;
	itoa[size] = '\0';
	size--;
	while (n != 0)
	{
		if (n < 0)
			itoa[size] = -(n % 10) + '0';
		else
			itoa[size] = n % 10 + '0';
		size--;
		n = n / 10;
	}
	return (itoa);
}

char	*ft_itoa(int n)
{
	int		size;

	if (n == 0)
		return (s_zero());
	if (n == -2147483648)
		return (s_intmin());
	size = s_n_length(n);
	return (s_itoa(size, n));
}
