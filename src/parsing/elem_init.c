#include "cub.h"

void	assign_color(t_cub *cub, int type)
{
	if (type == NO)
		cub->elem[NO].back_up = 4210944;
	else if (type == SO)
		cub->elem[SO].back_up = 6908313;
	else if (type == WE)
		cub->elem[WE].back_up = 12632352;
	else if (type == EA)
		cub->elem[EA].back_up = 14660672;
	else if (type == F)
		cub->elem[F].back_up = 14553600;
	else if (type == C)
		cub->elem[C].back_up = 14872320;
	else if (type == D)
		cub->elem[D].back_up = 9127219;
}

void	load_or_assign_color(t_cub *cub, char *description, int type)
{
	int	color;

	if (!description)
		assign_color(cub, type);
	else
	{
		color = make_color(description);
		if (color == -1)
		{
			assign_color(cub, type);
		}
		else
		{
			cub->elem[type].color = color;
		}
	}
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
			cub->elem[type].texture.mlx_img = mlx_xpm_file_to_image(cub->mlx, path, &cub->w, &cub->h);
		}
		if (cub->elem[type].texture.mlx_img)
			init_image_address(&cub->elem[type].texture);
		else
			load_or_assign_color(cub, cub->elem[type].description, type);
		type++;
	}
}
