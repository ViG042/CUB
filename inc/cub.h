/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:47:57 by mkling            #+#    #+#             */
/*   Updated: 2025/04/02 12:48:32 by mkling           ###   ########.fr       */
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
# define WIN_WIDTH 1200
# define WIN_HEIGHT 900
# define MINIMAP_PROPORTION 0.5
# define CURSOR_SIZE 10
# define UNIT 10
# define WIN_NAME "CUB3D"
# define SPEED 0.5
# define ROT_SPEED 50
# define WAND 0.25
# define FIELD_OF_VIEW 60

/* COLORS */

# define TRANSPARENT 0x500000
# define BLACK 0x000000
# define WHITE 0xffffff
# define GREY 0x555555
# define DARK_GREY 0x222222
# define ORANGE 0xFFFF00
# define BLUE 0x1111FF
# define VIOLET 0xFF00FF
# define TEAL 0x00FFFF
# define GREEN 0x00F500
# define YELLOW 0xFF0055
# define DIMBROWN 0x5A4A3F
# define LIGHTGREY 0xA9A9A9
# define PEACH 0xFFDAB9
# define WARMORANGE 0xFFB347
# define LIGHTBLUE 0x87CEEB
# define CHOCO 0xD2691E

typedef unsigned char	t_byte;

typedef struct s_point
{
	float	x;
	float	y;
	char	type;
}	t_pt;

typedef struct s_pixel
{
	int		x;
	int		y;
}	t_pix;

typedef struct s_maptile
{
	int		x;
	int		y;
	int		type;
	float	state;
}	t_tile;

typedef struct s_color
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;
	float	ratio;
}	t_color;

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
	char	**clean_map;
	t_tile	**tiles;
	int		width;
	int		height;
	int		size;
	int		cursor_size;
	int		tile_size;
	int		scale;
	int		offset_x;
	int		offset_y;
	int		pt_count;
}	t_map;

typedef struct s_elem
{
	char	*description;
	t_img	texture;
	int		color;
	int		back_up;
	int		width;
	int		height;
}	t_elem;

typedef struct s_display
{
	long long	last_frame;
	float		delta_time;
	float		fps;
	float		counter;
	int			mid_x;
	int			mid_y;
}	t_disp;

typedef struct s_key_states
{
	bool	left;
	bool	right;
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	int		mouse_x;
	int		mouse_y;
}	t_key;

typedef struct s_player
{
	float	angle;
	t_pt	map_pt;
	t_pt	grid_pt;
	t_pt	cursor[3];
	float	edge[4];
}	t_play;

typedef struct s_rayhit
{
	float	texture_offset;
	float	distance;
	int		height;
	int		top_pixel;
	int		end_pixel;
	float	angle;
	int		side;
	int		type;
	t_tile	*tile;
}	t_hit;

typedef struct s_ray
{
	float	angle_deg;
	float	angle_rad;
	t_pt	dist;
	t_pt	dda;
	t_pt	offset_to_edge;
	int		y;
	int		x;
	int		step_x;
	int		step_y;
	int		side;
	t_hit	hit[10];
	int		hit_count;
}	t_ray;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	t_elem	elem[10];
	t_map	*map;
	t_img	visual;
	t_key	keys;
	t_play	player;
	t_disp	display;
	char	temp_map[MAX_TEMP_MAP];
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

void	initialize_player(t_cub *cub, float x, float y, int orientation);
int		handle_input(int keysym, int mode, t_cub *cub);
int		handle_input_release(int keysym, t_cub *cub);
int		handle_input_press(int keysym, t_cub *cub);
int		handle_mouse(int x, int y, t_cub *cub);
void	move_player(t_cub *cub);
void	check_collision(t_map *map, const t_pt *player_grid, t_pt *direction);

/* DISPLAY */

void	init_display(t_cub *cub);
void	init_image_address(t_img *img);
int		render(t_cub *cub);
int		game_loop(void *voided_cub);
int		is_in_window(int x, int y);
void	update_delta_time(t_cub *cub);

/* PAINTING */

int		get_red(int color);
int		get_green(int color);
int		get_blue(int color);
int		encode_rgb(t_byte red, t_byte green, t_byte blue);
void	paint_pixel(t_img *img, int x, int y, int color);
int		read_pixel(t_img *img, int img_width, int img_height, t_pix pixel);
void	paint_pixel_blend(t_img *img, int x, int y, int color);
void	paint_background(t_img *img, int color);
void	paint_line(t_pt start, t_pt end, t_cub *cub);
void	update_player_cursor(t_cub *cub);
void	paint_square(t_img *img, t_pt *pt, int size, int color);
void	paint_triangle(t_img *img, t_pt coordinates[3], int color);
int		shade_left_right(t_hit *block, int color);
int		shade_up_down(int row, int color);
int		blend(int color1, int color2, float ratio);

/* TRANSFORM */

void	transform_map_into_tiles(t_cub *cub);
void	init_angles_offsets(t_cub *cub);
void	rotate_point(t_pt *point, t_pt *center, float angle);
void	init_minimap(t_map *map);
t_pt	scale_point(t_pt pt, int scale);

/* RAYCASTING */

void	raycasting(t_cub *cub);
void	define_collision_side(t_hit *block, t_ray *ray);
void	identify_block(t_hit *block, t_ray *ray, t_map *map, t_pt player_pos);
void	paint_column(t_cub *cub, t_hit *block, int column, int is_last_block);

/* MATH */

float	fclamp(float value, float min, float max);

enum e_errcode
{
	SUCCESS,
	WRONG_ARG,
	OPEN_FAIL,
	READ_FAIL,
	TOO_BIG,
	NO_SPRITE,
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
	MAP_NOT_VALID,
	NO_PLAYER,
	TOO_MANY_PLAYER,
	BAD_WALLING,
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
	NONUM = 0,
	NORTH = 1,
	SOUTH = 2,
	WEST = 3,
	EAST = 4,
};

enum e_block_type
{
	EMPTY = '0',
	WALL = '1',
	DOOR = 'D',
	GOLEM = 'G',
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
	G,
};

#endif
