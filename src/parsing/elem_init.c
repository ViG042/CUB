#include "cub.h"

void	assign_color(t_cub *cub, int type)
{
	if (type == NO)
		cub->elem[NO].back_up = DIMBROWN;
	else if (type == SO)
		cub->elem[SO].back_up = LIGHTGREY;
	else if (type == WE)
		cub->elem[WE].back_up = GREY;
	else if (type == EA)
		cub->elem[EA].back_up = PEACH;
	else if (type == F)
		cub->elem[F].back_up = WARMORANGE;
	else if (type == C)
		cub->elem[C].back_up = LIGHTBLUE;
	else if (type == D)
		cub->elem[D].back_up = CHOCO;
}

void	load_or_assign_color(t_cub *cub, char *description, int type)
{
	if (!description)
		assign_color(cub, type);
	else
	{
		cub->elem[type].color = make_color(description);
		if (cub->elem[type].color == -1)
			assign_color(cub, type);
	}
	cub->elem[type].height = 64;
	cub->elem[type].width = 64;
}

void	elem_init(t_cub *cub)
{
	int		type;
	char	*path;

	type = NO;
	while (type <= D)
	{
		if (cub->elem[type].description)
		{
			path = cub->elem[type].description;
			cub->elem[type].texture.mlx_img = mlx_xpm_file_to_image(cub->mlx,
					path, &cub->elem[type].width, &cub->elem[type].height);
		}
		if (cub->elem[type].texture.mlx_img)
			init_image_address(&cub->elem[type].texture);
		else
			load_or_assign_color(cub, cub->elem[type].description, type);
		type++;
	}
}
