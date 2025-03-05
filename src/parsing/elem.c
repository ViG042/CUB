#include "cub.h"

int	is_elem(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (E_NO);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (E_SO);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return (E_WE);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (E_EA);
	if (line[i] == 'F' && line[i + 1] == ' ')
		return (E_F);
	if (line[i] == 'C' && line[i + 1] == ' ')
		return (E_C);
	return (0);
}

void	assign_elem(t_cub *cub, int type, char *temp)
{
	printf("temp=[%s], adress=[%p]\n", temp, temp);////////
	 if (type == E_NO)
	 	cub->elem.no = temp;
	if (type == E_SO)
		cub->elem.so = temp;
	if (type == E_WE)
		cub->elem.we = temp;
	if (type == E_EA)
		cub->elem.ea = temp;
	if (type == E_F)
		cub->elem.f = temp;
	if (type == E_C)
		cub->elem.c = temp;
}

void	copy_elem(t_cub *cub, char *line, int type, char *temp, int start)
{
	int	i;

	i = 0;
	while (line[start + i] != ' ' && line[start + i] != '\n'
		&& line[start + i] != '\0' )// /0 utile ? utile si pas de carte derriere le dernier elem
	{
		temp[i] = line[start + i];
		i++;
	}
	temp[i] = '\0';
	printf("temp=[%s], adress=[%p]\n", temp, temp);////////
	assign_elem(cub, type, temp);
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
	// else
	// {
	// 	//wrong syntax
	// 	return ;
	// }
	printf("line=[%s], i=[%d]\n", line, i);/////
	while (line[i + size] != ' ' && line[i + size] != '\n'
		&& line[i + size] != '\0' )// /0 utile ?
		size++;
	printf("size=[%d]\n", size);//////////
	temp = malloc(size + 1);
	if (!temp)
	{
		//malloc error
		return ;
	}
	copy_elem(cub, line, type, temp, i);
}

int	duplicata_error(t_cub *cub, int type)
{
	if ((type == E_NO && cub->elem.no) || (type == E_SO && cub->elem.so)
		|| (type == E_WE && cub->elem.we) || (type == E_EA && cub->elem.ea)
		|| (type == E_F && cub->elem.f) || (type == E_C && cub->elem.c))
	{
		return (1);
	}
	return (0);
}

void	extract_elem(t_cub *cub)
{
	int	i;
	int	type;

	i = 0;
	while (cub->map->array[i])
	{
		type = is_elem(cub->map->array[i]);
		exit_if(type && duplicata_error(cub, type), DOUBLE_ELEM, cub);
		printf("type=%d\n", type);///////
		if (type)
			load_elem(cub, cub->map->array[i], type);
		// wrong syntax or malloc error -> return
		i++;
	}
}
