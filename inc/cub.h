/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodoy <vgodoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:54:35 by vgodoy            #+#    #+#             */
/*   Updated: 2025/03/13 17:38:40 by vgodoy           ###   ########.fr       */
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
# include <sys/time.h>
# include "minilibx-linux/mlx.h"
# include "libft/inc/libft.h"


/* MATH */

// Approximation of pi
# define PI 3.14159265
// aproximation of one radian (PI / 180)
# define RADIAN 0.0174532925

/* GENERAL VALUES */

# define MAX_TEMP_MAP 4096
# define WIN_WIDTH 500//1920
# define WIN_HEIGHT 500//1010
# define MINIMAP_PROPORTION 0.8
# define CURSOR_SIZE 10
# define UNIT 10
# define WIN_NAME "CUB3D"
# define BLACK 0x000000
# define WHITE 0xffffff
# define GREY 0x555555
# define DARK_GREY 0x222222
# define ORANGE 0xFFA500
# define SPEED 2
# define WAND 0.2
# define FIELD_OF_VIEW 60

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
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
	double	length;
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
	char	**array;//free lines and array
	char	**clean_map;//free only clean_map
	t_pt	**pts;
	int		width;
	int		height;
	int		size;
	int		minimap_max_width;
	int		minimap_max_height;
	int		tile_size;
	int		scale;
	int		offset_x;
	int		offset_y;
	int		pt_count;
}	t_map;

typedef struct s_elem
{
	char	*description;
	void	*texture;
	int		color;
	int		back_up;
}	t_elem;

typedef struct s_display
{
	long long	last_frame;
	double		delta_time;
	double		fps;
	double		counter;
}	t_disp;

typedef struct s_key_states
{
	bool	left;
	bool	right;
	bool	w;
	bool	a;
	bool	s;
	bool	d;
}	t_key;

typedef	struct s_player
{
	double	player_angle;
	char	init_orientation;
	t_pt	map_pt;
	t_pt	grid_pt;
	t_pt	cursor[3];
	double	edge[4];
	int		cursor_size;
}	t_play;

typedef struct s_cub
{
	int		w;		///permet d'utiliser la fonction
	int		h;		//mlx_xpm_file_to_image()
	void	*mlx;
	void	*win;
	t_elem	elem[10];
	t_map	*map;
	t_map	*world;
	t_img	hud;
	t_img	img;
	t_key	keys;
	t_play	player;
	t_disp	display;
	int		fd;
	char	temp_map[MAX_TEMP_MAP];
	int		offset_x;
	int		offset_y;
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
int		dbl_elem(int type, char *description);
int		elem_missing(t_cub *cub);
void	elem_extract(t_cub *cub);
void	elem_init(t_cub *cub);
int		make_color(char *description);
void	map_check(t_cub *cub);
void	map_clean(t_cub *cub);
char	*talking_textures(int type);
void	print_info(char **array);
void	print_elem(t_cub *cub);
void	print_init_elem(t_cub *cub);
void	print_map(char **map);

/* INPUTS */

int		handle_input(int keysym, int mode, t_cub *cub);
void	initialize_player(t_cub *cub, t_pt *start);
int		handle_input_release(int keysym, t_cub *cub);
int		handle_input_press(int keysym, t_cub *cub);
void	move_player(t_cub *cub);

/* DISPLAY */

void	init_window(t_cub *cub);
void	init_display(t_cub *cub);
int		render(t_cub *cub);
int		game_loop(void *voided_cub);
int		is_in_window(int x, int y);
void	update_delta_time(t_cub *cub);

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
void	rotate_point(t_cub *cub, t_pt *point, t_pt *center, double angle);
void	rotate(t_cub *cub);
void	project_map(t_cub *cub);
t_pt	project_point(t_cub	*cub, t_pt pt);

/* RAYCASTING */

void	raycasting(t_cub *cub);


enum e_errcode {
	SUCCESS,
	WRONG_ARG,
	OPEN_FAIL,
	READ_FAIL,
	TOO_BIG,//
	NO_SPRITE,//
	NOT_RECT,
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
	NO_MAP,
	MAP_NOT_VALID,//
	NO_PLAYER,
	TOO_MANY_PLAYER,
	BAD_WALLING,//
	ASTRONAUT,
	DEADLY_PATH,
	DEADLY_DOOR,
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

enum e_orient
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
};

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

enum e_raycast
{
	ANGLE_DEG,    //from 0 to 360
	ANGLE_RAD,    //from -1 to 1
	DIST_X,       //dist entre les colonnes
	DIST_Y,       //dist entre les lignes
	FIRST_X,      //premiere dist vers colonne
	FIRST_Y,      //permiere dist vers ligne
	DIST_TO_WALL,
	START_PAINT,   //from the top
	STOP_PAINT,    //to the bottom
};

enum e_raycast2
{

	X,            // X et Y permettent de se deplacer dans clean_map
	Y,            // et de memoriser la case vue en premier par le rayon
	STEP_X,       // STEP_X et STEP_Y permettent de sauvegarder le step
	STEP_Y,       // en X ou Y : 1 ou -1 en fonction de l'angle
};

#endif
