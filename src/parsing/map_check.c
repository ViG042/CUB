#include "cub.h"

// exit_if(!is_valid_line(cub->map->array[line]), MAP_NOT_VALID, cub);

int	how_many_players(t_cub *cub)
{
	int		player;
	int		line;
	int		i;
	char	c;

	player = 0;
	line = 0;
	while (cub->map->clean_map[line])
	{
		i = 0;
		while (cub->map->clean_map[line][i])
		{
			c = cub->map->clean_map[line][i];
			if (c == 'N' || c == 'S'
				|| c == 'W' || c == 'E')
			{
				player++;
			}
			i++;
		}
		line++;
	}
	return (player);
}

int	check_walls(t_cub *cub)
{
	(void)cub;
	return (1);
}

void	map_check(t_cub *cub)
{
	exit_if(!check_walls(cub), BAD_WALLING, cub);
	printf("The map is correctly walled\n");
	exit_if(how_many_players(cub) < 1, NO_PLAYER, cub);
	exit_if(how_many_players(cub) > 1, TOO_MANY_PLAYER, cub);
	printf("The player is ready to go\n");
}

// static int	check_walls(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	while (cub->map->array[0][x] == '1')
// 		x++;
// 	if (x != cub->map->width)
// 		return (0);
// 	x = 0;
// 	while (cub->map->array[cub->map->height - 1][x] == '1')
// 		x++;
// 	if (x != cub->map->width)
// 		return (0);
// 	y = 0;
// 	while (cub->map->array[y] && cub->map->array[y][0] == '1')
// 		y++;
// 	if (y != cub->map->height)
// 		return (0);
// 	y = 0;
// 	while (cub->map->array[y] && cub->map->array[y][cub->map->width - 1] == '1')
// 		y++;
// 	if (y != cub->map->height)
// 		return (0);
// 	return (1);
// }
