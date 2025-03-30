#include "cub.h"

static void	define_surface_till_90(t_hit *block, t_ray *ray)
{
	if (ray->side == TOP)
		block->side = NORTH;
	else
		block->side = EAST;
}

static void	define_surface_till_180(t_hit *block, t_ray *ray)
{
	if (ray->side == TOP)
		block->side = SOUTH;
	else
		block->side = EAST;
}

static void	define_surface_till_270(t_hit *block, t_ray *ray)
{
	if (ray->side == TOP)
		block->side = SOUTH;
	else
		block->side = WEST;
}

static void	define_surface_till_360(t_hit *block, t_ray *ray)
{
	if (ray->side == TOP)
		block->side = NORTH;
	else
		block->side = WEST;
}

void	define_collision_side(t_hit *block, t_ray *ray)
{
	if (ray->angle_deg < 90)
		return (define_surface_till_90(block, ray));
	if (ray->angle_deg < 180)
		return (define_surface_till_180(block, ray));
	if (ray->angle_deg < 270)
		return (define_surface_till_270(block, ray));
	else
		return (define_surface_till_360(block, ray));
}
