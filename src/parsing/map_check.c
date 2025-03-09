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
				cub->player.init_orientation = c;
				player++;
			}
			i++;
		}
		line++;
	}
	return (player);
}

/*' ' <- space is NOT a valid char here*/
int	is_not_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'D'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' )
	{
		return (0);
	}
	return (1);
}

int	invalid_flooring(t_cub *cub, char **map, int line, int i)
{
	char	c;

	c = map[line][i];
	if (i == 0 || !map[line][i + 1] || line == 0 || !map[line]
		|| is_not_valid_char(map[line -1][i])
		|| is_not_valid_char(map[line + 1][i])
		|| is_not_valid_char(map[line][i - 1])
		|| is_not_valid_char(map[line][i + 1]))
	{
		printf("map[line=%d][collumn=%d] = %c\n", line, i, map[line][i]);
		exit_if((c == 'N' || c == 'S'), ASTRONAUT, cub);
		exit_if((c == 'W' || c == 'E'), ASTRONAUT, cub);
		exit_if(c == '0', DEADLY_PATH, cub);
		exit_if(c == 'D', DEADLY_DOOR, cub);
		return (1);
	}
	return (0);
}

int	bad_walls(t_cub *cub)
{
	int		line;
	int		i;
	char	**map;

	map = cub->map->clean_map;
	line = 0;
	while (map[line])
	{
		i = 0;
		while (map[line][i])
		{
			if (map[line][i] == '0' || map[line][i] == 'D'
				|| map[line][i] == 'N' || map[line][i] == 'S'
				|| map[line][i] == 'W' || map[line][i] == 'E')
			{
				if (invalid_flooring(cub, map, line, i))
					return (1);
			}
			i++;
		}
		line++;
	}
	return (0);
}

void	map_check(t_cub *cub)
{
	exit_if(how_many_players(cub) < 1, NO_PLAYER, cub);
	exit_if(how_many_players(cub) > 1, TOO_MANY_PLAYER, cub);
	printf("One player is what we need\n");
	bad_walls(cub);
	printf("The map is correctly walled\n");
	printf("\n🚀 Map check-list complete\n\n");
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
