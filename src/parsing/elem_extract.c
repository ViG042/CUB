#include "cub.h"

int	is_elem(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (NO);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (SO);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return (WE);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (EA);
	if (line[i] == 'F' && line[i + 1] == ' ')
		return (F);
	if (line[i] == 'C' && line[i + 1] == ' ')
		return (C);
	if (line[i] == 'D' && line[i + 1] == ' ')
		return (D);
	return (0);
}

void	copy_elem(t_cub *cub, char *line, int type, char *temp, int start)
{
	int	i;

	i = 0;
	while (line[start + i] != ' ' && line[start + i] != '\n'
		&& line[start + i] != '\0' )
	{
		temp[i] = line[start + i];
		i++;
	}
	temp[i] = '\0';
	cub->elem[type].description = temp;
}

void	load_elem(t_cub *cub, char *line, int type)
{
	int		i;
	int		size;
	char	*temp;

	i = 0;
	size = 0;
	while (line[i] == ' ')
		i++;
	i = i + 2;
	while (line[i] == ' ')
		i++;
	if (line[i] == '.' && line[i + 1] == '/')
		i = i + 2;
	while (line[i + size] != ' ' && line[i + size] != '\n'
		&& line[i + size] != '\0' )
		size++;
	exit_if(size == 0, EMPTY_ELEM, cub);
	temp = malloc(size + 1);
	exit_if(!temp, MALLOC_FAIL, cub);
	copy_elem(cub, line, type, temp, i);
}

//eventuellement a regarder les elems lorsque l'on commence a voir la map
void	elem_extract(t_cub *cub)
{
	int	i;
	int	type;

	i = 0;
	while (cub->map->array[i])
	{
		type = 0;
		type = is_elem(cub->map->array[i]);
		exit_if(dbl_elem(type, cub->elem[type].description), DBL_ELEM, cub);
		if (type)
			load_elem(cub, cub->map->array[i], type);
		i++;
	}
	exit_if(elem_missing(cub), ELEM_MSSG, cub);
}
