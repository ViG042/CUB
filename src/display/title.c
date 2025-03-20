#include "cub.h"

void	print_title_screen(t_cub *cub)
{
	paint_background(&cub->img, BLACK);
	cub->img.mlx_img = mlx_xpm_file_to_image(cub->mlx, "assets/wall1.xpm", &cub->w, &cub->h);
	if (!cub->img.mlx_img)
		printf("error\n");
}
