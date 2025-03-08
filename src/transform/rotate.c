/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:02:27 by mkling            #+#    #+#             */
/*   Updated: 2025/03/08 14:35:14 by alex             ###   ########.fr       */
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
Generate a rotation matrix on the y axis such as
[ cos(angle) & 0 & sin(angle)]
[ 0 & 1 & 0]
[ -sin(angle) & 0 & cos(angle)]
*/
void	generate_translation_matrix(t_cub *cub, float matrix[3][3])
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = cub->player.sh;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = cub->player.sh;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;

	fprintf(stderr, "tx is %f\n", cub->player.sh);
}

void	matrix_multiply(float result[3][3], float mat1[3][3], float mat2[3][3])
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			result[i][j] = 0;
			k = 0;
			while (k < 3)
			{
				result[i][j] += mat1[i][k] * mat2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
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
	float	matrix_t[3][3];
	float	combined_matrix[3][3];
	float	ult_matrix[3][3];

	index = 0;
	cub->minimap = cub->map;
	generate_rotation_matrix_x(cub->angle_x_axis, matrix_x);
	generate_rotation_matrix_y(cub->angle_y_axis, matrix_y);
	generate_translation_matrix(cub, matrix_t);
	matrix_multiply(combined_matrix, matrix_t, matrix_y);
	matrix_multiply(ult_matrix, combined_matrix, matrix_x);
	while (index < cub->map->size)
	{
		subtract_grid_center(&cub->minimap->pts_array[index], cub);
		multiply_point_by_matrix(&cub->minimap->pts_array[index], ult_matrix);
		add_grid_center(&cub->minimap->pts_array[index], cub);
		index++;
	}
}

void	rotate_player(t_cub *cub)
{
	float	matrix_x[3][3];
	float	matrix_y[3][3];
	float	matrix_sh[3][3];
	float	combined_matrix[3][3];
	float	ult_matrix[3][3];

	generate_rotation_matrix_x(cub->angle_x_axis, matrix_x);
	generate_rotation_matrix_y(cub->angle_y_axis, matrix_y);
	generate_translation_matrix(cub, matrix_sh);
	matrix_multiply(combined_matrix, matrix_sh, matrix_y);
	matrix_multiply(ult_matrix, combined_matrix, matrix_x);
	multiply_point_by_matrix(&cub->player, ult_matrix);
}

t_pt normalize_vector(t_pt *point)
{
	t_pt	unit_vector;
	float	magnitude;

	unit_vector = *point;
	magnitude = sqrt(point->x * point->x + point->y * point->y);
	if (magnitude != 0)
		unit_vector.x /= magnitude;
	if (point->y != 0)
		unit_vector.y /= magnitude;
	return (unit_vector);
}

void	rotate_point(t_cub *cub, t_pt *point, t_pt *center, float angle)
{
	float	radian;
	float	cos_angle;
	float	sin_angle;
	t_pt	centered;
	t_pt	rotated;

	(void)cub;
	fprintf(stderr, "point %f %f ", point->x, point->y);
	centered.x = point->x - center->x;
	centered.y = point->y - center->y;
	radian = angle * RADIAN;
	cos_angle = cos(radian);
	sin_angle = sin(radian);
	rotated.x = cos_angle * centered.x - sin_angle * centered.y;
	rotated.y = sin_angle * centered.x + cos_angle * centered.y;
	point->x = rotated.x + center->x;
	point->y = rotated.y + center->y;
	fprintf(stderr, " is %f %f\n", point->x, point->y);
}


