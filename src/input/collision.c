#include "cub.h"

/*			printf("cub->map->pts[y=%d][x=%d].type == '1'\n", y, x);///////*/
static int	is_wall(t_cub *cub, int x, int y)
{
	if (cub->map->pts[y][x].type)
	{
		if (cub->map->pts[y][x].type == '1')
			return (1);
		if (cub->map->pts[y][x].type == 'D')
			return (1);
	}
	return (0);
}

/*		printf("where=[%d], dist=[%f]\n", where, dist);*/
int	too_close(float x, float y, int where)
{
	float	wand;
	float	dist;

	wand = WAND;
	dist = 1;
	if (where == NORTH)
		dist = y - floor(y);
	else if (where == SOUTH)
		dist = ceil(y) - y;
	else if (where == WEST)
		dist = x - floor(x);
	else if (where == EAST)
		dist = ceil(x) - x;
	if (dist < wand)
		return (1);
	return (0);
}

/*Pour chacune des 4 directions
Si un mouvement se fait dans cette direction
Si une case plus loin dans cette direction on a un mur
Si la procimite a ce mur est inferieur a wand
Alors on annule le mouvement dans cette direction
	printf("player position x=[%f] y=[%f]\n\n", x ,y);///*/
void	check_collision(t_cub *cub, t_pt *direction)
{
	float	x;
	float	y;

	x = cub->player.grid_pt.x;
	y = cub->player.grid_pt.y;
	if (direction->y < 0
		&& is_wall(cub, x, y - 1)
		&& too_close(x, y, NORTH))
		direction->y = 0;
	else if (direction->y > 0
		&& is_wall(cub, x, y + 1)
		&& too_close(x, y, SOUTH))
		direction->y = 0;
	if (direction->x < 0
		&& is_wall(cub, x - 1, y)
		&& too_close(x, y, WEST))
		direction->x = 0;
	else if (direction->x > 0
		&& is_wall(cub, x + 1, y)
		&& too_close(x, y, EAST))
		direction->x = 0;
}
