/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:02:27 by mkling            #+#    #+#             */
/*   Updated: 2025/03/04 13:30:43 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
Generate a rotation matrix on the x axis such as
[ 1 & 0 & 0 ]
[ 0 & cos(angle) & -sin(angle) ]
[ 0 & sin(angle) & cos(angle) ]
*/
void	generate_rotation_matrix_x(float angle, float matrix[3][3])
{
	float	cosinus;
	float	sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = cosinus;
	matrix[1][2] = -sinus;
	matrix[2][0] = 0;
	matrix[2][1] = sinus;
	matrix[2][2] = cosinus;
}

/*
Generate a rotation matrix on the y axis such as
[ cos(angle) & 0 & sin(angle)]
[ 0 & 1 & 0]
[ -sin(angle) & 0 & cos(angle)]
*/
void	generate_rotation_matrix_y(float angle, float matrix[3][3])
{
	float	cosinus;
	float	sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	matrix[0][0] = cosinus;
	matrix[0][1] = 0;
	matrix[0][2] = sinus;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = -sinus;
	matrix[2][1] = 0;
	matrix[2][2] = cosinus;
}

/*
Generate a rotation matrix on the z axis such as
[ cos(angle) & -sin(angle) & 0 ]
[ sin(angle) & cos(angle) & 0 ]
[ 0 & 0 & 1 ]
*/
void	generate_rotation_matrix_z(float angle, float matrix[3][3])
{
	float	cosinus;
	float	sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	matrix[0][0] = cosinus;
	matrix[0][1] = -sinus;
	matrix[0][2] = 0;
	matrix[1][0] = sinus;
	matrix[1][1] = cosinus;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

void	multiply_point_by_matrix(t_pt *point, float matrix[3][3])
{
	t_pt	result;

	result.x = point->x * matrix[0][0]
		+ point->y * matrix[0][1]
		+ point->z * matrix[0][2];
	result.y = point->x * matrix[1][0]
		+ point->y * matrix[1][1]
		+ point->z * matrix[1][2];
	result.z = point->x * matrix[2][0]
		+ point->y * matrix[2][1]
		+ point->z * matrix[2][2];
	point->x = result.x;
	point->y = result.y;
	point->z = result.z;
}

void	rotate(t_cub *cub)
{
	int		index;
	float	matrix_x[3][3];
	float	matrix_y[3][3];
	float	matrix_z[3][3];

	index = 0;
	generate_rotation_matrix_x(cub->angle_x_axis, matrix_x);
	generate_rotation_matrix_y(cub->angle_y_axis, matrix_y);
	generate_rotation_matrix_z(cub->angle_z_axis, matrix_z);
	while (index < cub->map->size)
	{
		subtract_grid_center(&cub->map->pts_array[index], cub);
		multiply_point_by_matrix(&cub->map->pts_array[index], matrix_z);
		multiply_point_by_matrix(&cub->map->pts_array[index], matrix_y);
		multiply_point_by_matrix(&cub->map->pts_array[index], matrix_x);
		add_grid_center(&cub->map->pts_array[index], cub);
		index++;
	}
}
