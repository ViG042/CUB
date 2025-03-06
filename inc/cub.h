/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:54:35 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/06 17:49:53 by vgodoy           ###   ########.fr       */
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

# define MAX_TEMP_MAP 4096
# define WIN_WIDTH 1200
# define WIN_HEIGHT 600
# define UNIT 10
# define WIN_NAME "CUB3D"
# define BLACK 0x000000
# define WHITE 0xffffff
# define GREY 0x555555

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		rgb;
	char	type;
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
	t_pt	*pts_array;
	int		width;
	int		height;
	int		size;
}	t_map;

enum e_elem
{
	NO = 1,
	SO,
	WE,
	EA,
	F,
	C,
	D,
};

typedef struct s_elem
{
	char	*description;
	void	*texture;
	int		color;
	int		back_up;
}	t_elem;

typedef struct s_cub
{
	int		w;///permet d'utiliser la fonction
	int		h;//mlx_xpm_file_to_image()
	void	*mlx;
	void	*win;
	t_elem	elem[10];
	t_map	*map;
	t_map	*local;
	t_img	minimap;
	t_img	img;
	int		fd;
	char	temp_map[MAX_TEMP_MAP];
	int		mvt;
	t_pt	player;
	int		p_x;
	int		p_y;
	int		offset_x;
	int		offset_y;
	float	angle_y_axis;
	float	angle_x_axis;
	float	angle_z_axis;
	int		count;
	int		zoom;
	int		unit;
}	t_cub;

/* ERROR HANDLING */

void	exit_if(int condition, int err_num, t_cub *cub);
void	soft_exit_if(int condition, int err_num);
void	wipe(t_cub *cub);
int		success_exit(t_cub *cub);

/* PARSING */

void	parse_file(t_cub *cub);

void	check_arg_syntax(t_cub *cub, int argc, char **argv);
void	check_map_syntax(t_cub *cub);

int		dbl_elem(int type, char *description);
int		elem_missing(t_cub *cub);
void	elem_extract(t_cub *cub);
void	elem_init(t_cub *cub);
int		make_color(char *description);

void	map_check(t_cub *cub);

char	*talking_textures(int type);
void	print_split(char **array);
void	print_elem(t_cub *cub);
void	print_init_elem(t_cub *cub);

/* INPUTS */

int		handle_input(int keysym, t_cub *cub);
int		handle_mouse(int button, int x, int y, t_cub *cub);
void	initialize_player(t_cub *cub);

/* DISPLAY */

void	init_window(t_cub *cub);
int		render(t_cub *cub);

/* PAINTING */

void	put_point(t_cub *cub, t_pt point);
void	paint_pixel(t_img *img, int x, int y, int color);
void	paint_background(t_img *img, int color);
void	paint_line(t_pt start, t_pt end, t_cub *cub);
void	paint_minimap(t_cub *cub);
void	paint_square(t_cub *cub, t_pt *pt, int color);
void	paint_triangle(t_cub *cub, t_pt *pt, int color);

/* TRANSFORM */

void	transform_map_into_pts(t_cub *cub);
void	subtract_grid_center(t_pt *point, t_cub *cub);
void	add_grid_center(t_pt *point, t_cub *cub);
t_pt	apply_zoom_and_offset(t_pt *point, t_cub *cub);
void	init_angles_offsets(t_cub *cub);

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
	EMPTY_ELEM,
	DBL_ELEM,
	ELEM_MSSG,
};

enum	e_mouse
{
	RIGHT_CLICK = 1,
	LEFT_CLICK = 3,
	WHEEL_UP = 4,
	WHEEL_DOWN = 5,
};

#endif
