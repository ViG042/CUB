#include "cub.h"

static void	define_surface_till_90(t_cub *cub)
{
	if (cub->ray.side == TOP)
		cub->ray.side = NORTH;
	else
		cub->ray.side = EAST;
}

static void	define_surface_till_180(t_cub *cub)
{
	if (cub->ray.side == TOP)
		cub->ray.side = SOUTH;
	else
		cub->ray.side = EAST;
}

static void	define_surface_till_270(t_cub *cub)
{
	if (cub->ray.side == TOP)
		cub->ray.side = SOUTH;
	else
		cub->ray.side = WEST;
}

static void	define_surface_till_360(t_cub *cub)
{
	if (cub->ray.side == TOP)
		cub->ray.side = NORTH;
	else
		cub->ray.side = WEST;
}

void	define_collision_side(t_cub *cub)
{
	if (cub->ray.angle_deg < 90)
		return (define_surface_till_90(cub));
	if (cub->ray.angle_deg < 180)
		return (define_surface_till_180(cub));
	if (cub->ray.angle_deg < 270)
		return (define_surface_till_270(cub));
	else
		return (define_surface_till_360(cub));
}
