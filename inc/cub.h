/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:54:35 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/08 23:12:56 by alex             ###   ########.fr       */
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


/* MATH */

// Approximation of pi
# define PI 3.14159265
// aproximation of one radian (PI / 180)
# define RADIAN 0.0174532925

/* GENERAL VALUES */

# define WIN_WIDTH 1200
# define WIN_HEIGHT 600
# define CURSOR_SIZE 10
# define UNIT 10
# define WIN_NAME "CUB3D"
# define BLACK 0x000000
# define WHITE 0xffffff
# define GREY 0x555555
# define MINIMAP_OFFSET 20
# define MINIMAP_SCALE 20
# define MINIMAP_TILE_SIZE 18

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

typedef struct s_key_states
{
	bool	left;
	bool	right;
	bool	w;
	bool	a;
	bool	s;
	bool	d;
}	t_key;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_map	*minimap;
	t_map	*world;
	t_img	hud;
	t_img	img;
	t_key	keys;
	int		fd;
	char	temp_map[1024];
	int		mvt;
	t_pt	player;
	int		p_x;
	int		p_y;
	int		offset_x;
	int		offset_y;
	float	angle_y_axis;
	float	player_angle;
	int		count;
	int		zoom;
	int		unit;
}	t_cub;

/* ERROR HANDLING */

void	exit_if(int condition, int err_num, t_cub *cub);
void	soft_exit_if(int condition, int err_num);
void	wipe(t_cub *cub);
int		success_exit(t_cub *cub);

/* INPUTS */

int		handle_input(int keysym, int mode, t_cub *cub);
void	initialize_player(t_cub *cub);
int		handle_input_release(int keysym, t_cub *cub);
int		handle_input_press(int keysym, t_cub *cub);

/* DISPLAY */

void	init_window(t_cub *cub);
int		render(t_cub *cub);
int		game_loop(void *voided_cub);
int		is_in_window(int x, int y);

/* PARSING */

void	check_arg_syntax(t_cub *cub, int argc, char **argv);
void	check_map_syntax(t_cub *cub);
void	parse_map(t_cub *cub);

/* PAINTING */

void	put_point(t_cub *cub, t_pt point);
void	paint_pixel(t_img *img, int x, int y, int color);
void	paint_background(t_img *img, int color);
void	paint_line(t_pt start, t_pt end, t_cub *cub);
void	paint_minimap(t_cub *cub);
void	paint_square(t_img *img, t_pt *pt, int size, int color);
void	paint_triangle(t_img *img, t_pt coordinates[3], int color);

/* TRANSFORM */

void	transform_map_into_pts(t_cub *cub);
void	subtract_grid_center(t_pt *point, t_cub *cub);
void	add_grid_center(t_pt *point, t_cub *cub);
t_pt	apply_zoom_and_offset(t_pt *point, t_cub *cub);
void	init_angles_offsets(t_cub *cub);
void	rotate_point(t_cub *cub, t_pt *point, t_pt *center, float angle);
void	rotate_player(t_cub *cub);
void	rotate(t_cub *cub);
void	project(t_cub *cub);
void	orient_and_paint_player(t_cub *cub, t_pt *center, int size, int color);

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

enum	e_vertices
{
	TOP = 0,
	LEFT = 1,
	RIGHT = 2,
};

#endif
