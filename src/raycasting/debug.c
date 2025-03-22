#include "cub.h"

void	debug_print(t_cub *cub, int pixel_column)
{
	if (pixel_column == WIN_WIDTH / 2)
	{
		(void)cub;
		//printf("\n\npixel column is %d\n", pixel_column);
		//printf("wall hit at X=[%d] Y=[%d]\n", cub->ray.x, cub->ray.y);
		// printf("On side =[%d]\n", cub->ray.side);
		// printf("dda_x =[%f]\n", cub->ray.dda_x);
		// printf("dda_y =[%f]\n", cub->ray.dda_y);
		// printf("Wall distance =[%f]\n", cub->ray.wall_dist);
		// printf("angle deg =[%f]\n", cub->ray.angle_deg);
		// printf("sin angle deg =[%f]\n", sin(cub->ray.angle_deg));
		// printf("cos angle deg =[%f]\n", cos(cub->ray.angle_deg));
		// printf("pixel_column=[%d] angle_deg=[%f] angle_rad=[%f]
		// 	composante_x=[%f] composante_y=[%f] first_x[%f] first_y=[%f]
		// 	X=[%d] Y=[%d] STEP_X=[%d] STEP_Y=[%d]\n",
		// 	pixel_column, cub->ray.angle_deg, cub->ray.angle_deg,
		// 	cub->ray.dist_x, cub->ray.dist_y, cub->ray.firstx, cub->ray.firsty,
		// 	cub->ray.x, cub->ray.y, cub->ray.step_x, cub->ray.step_y);
		// printf("first wall pix is %d and last is %d\n",
		// 	cub->ray.top_wall, cub->ray.end_wall);
		printf("pretest dist in text=[%f]\n", cub->ray.dist_in_text);
		// printf("floor dist in text=[%f]\n", cub->ray.dist_in_text - floor(cub->ray.dist_in_text));
	}
}
