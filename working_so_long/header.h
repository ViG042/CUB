/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:29:15 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/03 11:49:27 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../inc/minilibx-linux/mlx.h"

typedef struct s_var
{
	int		fd;
	char	*map_name;
	char	temp_map[1024];
	char	**map;
	char	**map_copy;
	int		t;
	void	*mlx;
	void	*win;
	void	*coin;
	void	*eaux;
	void	*fire;
	void	*wall;
	void	*e042;
	void	*e000;
	void	*e025;
	void	*e050;
	void	*e075;
	void	*e100;
	void	*e125;
	void	*bou1;
	void	*bou2;
	void	*bou3;
	void	*bou4;
	int		mvt;
	int		i_player;
	int		i_exit;
	int		i_coin;
	int		i_boue;
	int		i_life;
	int		i_exit_copy;
	int		i_coin_reach;
	int		i_coin_copy;
	int		new_x;
	int		new_y;
	char	new_c;
	char	*itoa1;
	char	*itoa2;
	char	*itoa3;
	int		p_x;
	int		p_y;
	int		x_len;
	int		y_len;
}	t_cub;

char	*ft_itoa(int n);
int		basic_errors(int error);
int		errors(t_cub *v, int error);
int		parsing(t_cub *v);
char	**ft_split(char const *s, char c);
int		init_images(t_cub *v);
int		initialisations(t_cub *v, char *name);
int		start_flood_fill(t_cub *v);
void	free_maps(t_cub *v);
void	destroy_img(t_cub *v, int failed_img);
int		show_map(t_cub *v);
void	destroy_img(t_cub *v, int failed_img);
void	move(t_cub *v);
int		init_images(t_cub *v);
int		close_window(t_cub *v, int success);
int		check_walls(t_cub *v);
int		get_width_and_height(t_cub *v);

#endif
