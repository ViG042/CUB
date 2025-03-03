/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:54:35 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/03 15:29:32 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "minilibx-linux/mlx.h"
# include "libft/inc/libft.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 600
# define WIN_NAME "CUB3D"
# define BLACK 0x000000
# define WHITE 0xffffff

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		rgb;
}	t_pt;

typedef struct s_line
{
	t_pt	start;
	t_pt	current;
	t_pt	end;
	t_pt	delta;
	t_pt	sign;
	int		error;
	int		error2;
	float	length;
}	t_line;

typedef struct s_image
{
	void	*mlx_img;
	char	*address;
	int		bit_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	*name;
	char	**array;
	char	**split_by_line;
	int		*pts_array;
	int		width;
	int		height;
	int		total;
}	t_map;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	img;
	int		fd;
	char	temp_map[1024];
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
	int		offset_x;
	int		offset_y;
	float	angle_y_axis;
	float	angle_x_axis;
	float	angle_z_axis;
}	t_cub;

/* ERROR HANDLING */

void	exit_if(int condition, int err_num, t_cub *cub);
void	soft_exit_if(int condition, int err_num);
void	wipe(t_cub *cub);
int		success_exit(t_cub *cub);

/* INPUTS */

int		handle_input(int keysym, t_cub *cub);
int		handle_mouse(int button, int x, int y, t_cub *cub);

/* DISPLAY */

void	init_window(t_cub *cub);
int		render(t_cub *cub);

/* PARSING */

void	check_syntax(t_cub *cub, int argc, char **argv);
void	read_map_into_buffer(t_cub *cub);
void	parse_map(t_cub *cub);

/* PAINTING */

void	put_point(t_cub *cub, t_pt point);
void	paint_background(t_img *img, int color);
void	paint_line(t_pt start, t_pt end, t_cub *cub);







/* SO LONG */

// char	*ft_itoa(int n);
// int		basic_errors(int error);
// int		errors(t_cub *cub, int error);
// int		parsing(t_cub *cub);
// char	**ft_split(char const *s, char c);
// int		init_images(t_cub *cub);
// int		initialisations(t_cub *cub, char *name);
// int		start_flood_fill(t_cub *cub);
// void	free_maps(t_cub *cub);
// void	destroy_img(t_cub *cub, int failed_img);
// int		show_map(t_cub *cub);
// void	destroy_img(t_cub *cub, int failed_img);
// void	move(t_cub *cub);
// int		init_images(t_cub *cub);
// int		close_window(t_cub *cub, int success);
// int		check_walls(t_cub *cub);
// int		get_width_and_height(t_cub *cub);


enum e_errcode {
	SUCCESS,
	WRONG_ARG,
	OPEN_FAIL,
	READ_FAIL,
	TOO_BIG,
	NO_PLAYER,
	TOO_PLAYER,
	NO_SPRITE,
	NOT_RECT,
	NOT_WALLED,
	UNKNOWN,
	EMPTY_LINE,
	MAP_NAME,
	MLX_INIT,
	WIN_ALLOC,
	IMG_ALLOC,
	MALLOC_FAIL,
};

enum	e_mouse
{
	RIGHT_CLICK = 1,
	LEFT_CLICK = 3,
	WHEEL_UP = 4,
	WHEEL_DOWN = 5,
};

#endif
