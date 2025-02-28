/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:53:27 by vgodoy            #+#    #+#             */
/*   Updated: 2024/05/20 12:36:58 by vgodoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	how_many_strings(const char *s, char c)
{
	int	i;
	int	strings_counter;
	int	new_string;

	i = 0;
	strings_counter = 0;
	new_string = 1;
	while (s[i])
	{
		if (s[i + 1] && s[i] == c && s[i + 1] == c)
			return (0);
		if (s[i] == c)
			new_string = 1;
		if (s[i] != c && new_string)
		{
			strings_counter++;
			new_string = 0;
		}
		i++;
	}
	return (strings_counter);
}

static void	copy_string(const char *s, char c, char **page, int strings_counter)
{
	int	k;

	k = 0;
	while (s[k] && s[k] != c)
		k++;
	page[strings_counter] = malloc((k + 1) * sizeof(char));
	if (!page[strings_counter])
		return ;
	k = 0;
	while (s[k] && s[k] != c)
	{
		page[strings_counter][k] = s[k];
		k++;
	}
	page[strings_counter][k] = '\0';
}

static void	ft_free(char **page, int strings_counter)
{
	strings_counter--;
	while (strings_counter >= 0)
	{
		free(page[strings_counter]);
		strings_counter--;
	}
	free(page);
}

static void	fill_page_with_strings(const char *s, char c, char **page)
{
	int	i;
	int	strings_counter;
	int	new_string;

	i = 0;
	strings_counter = 0;
	new_string = 1;
	while (s[i])
	{
		if (s[i] == c)
			new_string = 1;
		if (s[i] != c && new_string)
		{
			copy_string(&s[i], c, page, strings_counter);
			if (!page[strings_counter])
			{
				ft_free(page, strings_counter);
				return ;
			}
			strings_counter++;
			new_string = 0;
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**page;
	int		so_much_strings;

	if (!s)
		return (NULL);
	so_much_strings = how_many_strings(s, c);
	if (!so_much_strings)
		return (basic_errors(7), NULL);
	page = malloc((so_much_strings + 1) * sizeof(char *));
	if (!page)
		return (NULL);
	fill_page_with_strings(s, c, page);
	if (!page)
		return (NULL);
	page[so_much_strings] = NULL;
	return (page);
}
/*
int	main(int argc, char **argv)
{
	(void)argc;
	char const *s = argv[1];
	char c = argv[2][0];
	char **page;
	int	i = 0;

	page = ft_split(s, c);
	if (!page)
	{
		printf("NuLl");
		return (0);
	}
	while (page[i] != 0)
	{
		printf("[%s] ", page[i]);
		i++;
	}
	printf("\n");
	return (0);
}
*/
