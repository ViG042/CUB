#include "cub.h"

void	distance_edge(t_cub *cub)
{
	//modf(cub->player.grid_pt.y, NULL)
	cub->player.edge[0] = 1 - (cub->player.grid_pt.y - floor(cub->player.grid_pt.y));
	cub->player.edge[1] = (cub->player.grid_pt.y - floor(cub->player.grid_pt.y));
	cub->player.edge[2] = 1 - (cub->player.grid_pt.x - floor(cub->player.grid_pt.x));
	cub->player.edge[3] = (cub->player.grid_pt.x - floor(cub->player.grid_pt.x));
	printf("edge N=[%f], S=[%f], W=[%f], E=[%f]", cub->player.edge[0], cub->player.edge[1],
		cub->player.edge[2], cub->player.edge[3]);
}


