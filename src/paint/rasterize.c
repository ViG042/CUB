/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:18:46 by mkling            #+#    #+#             */
/*   Updated: 2025/03/04 16:07:09 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	calculate_line_length(t_pt start, t_pt end)
{
	return (sqrtf((end.x - start.x) * (end.x - start.x)
			+ (end.y - start.y) * (end.y - start.y)));
}

float	calculate_progress(t_line *line, t_pt *current)
{
	float	progress;

	if (fabs(current->x - line->start.x) < 0.1
		&& fabs(current->y - line->start.y) < 0.1)
		progress = 0.0;
	else
		progress = calculate_line_length(line->start, line->current)
			/ line->length;
	return (progress);
}

void	print_line(t_line *line, t_cub *cub)
{
	line->current = line->start;
	while (1)
	{
		put_point(cub, line->current);
		line->error2 = 2 * line->error;
		if (line->error2 >= line->delta.y)
		{
			if ((int)line->current.x == (int)line->end.x)
				break ;
			line->error += line->delta.y;
			line->current.x += line->sign.x;
		}
		if (line->error2 <= line->delta.x)
		{
			if ((int)line->current.y == (int)line->end.y)
				break ;
			line->error += line->delta.x;
			line->current.y += line->sign.y;
		}
	}
}

void	paint_line(t_pt start, t_pt end, t_cub *cub)
{
	t_line	line;

	line.start = start;
	line.end = end;
	line.sign.x = 1.0;
	line.sign.y = 1.0;
	line.delta.x = ft_abs(line.end.x - line.start.x);
	if (line.start.x > line.end.x)
		line.sign.x = -1.0;
	line.delta.y = -ft_abs(line.end.y - line.start.y);
	if (line.start.y > line.end.y)
		line.sign.y = -1.0;
	line.error = line.delta.x + line.delta.y;
	line.length = calculate_line_length(line.start, line.end);
	print_line(&line, cub);
}
