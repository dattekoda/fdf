/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:29:24 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/06 00:30:28 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_point	change(t_point p, t_move *move, t_map *map);

void	draw_map(t_img *img, t_map *map, t_move *move)
{
	int		x;
	int		y;
	int		*s_col;
	t_point	start;
	int		*col;

	y = -1;
	col = map->map_color;
	while (++y < map->height - 1)
	{
		x = -1;
		while (++x < map->width - 1)
		{
			s_col = &col[y * map->width + x];
			start = change((t_point){x, y, *s_col}, move, map);
			draw_line(img, start,
				change((t_point){x + 1, y, *(s_col + 1)}, move, map));
			draw_line(img, start,
				change((t_point){x, y + 1, *(s_col + map->width)}, move, map));
		}
	}
}

static void	calc_rotate(double *a, double *b, double theta, t_point genten)
{
	double	tmp;

	tmp = *a;
	*a = *a * cos(theta) - *b * sin(theta)
		+ genten.x * (1 - cos(theta)) + genten.y * sin(theta);
	*b = tmp * sin(theta) + *b * cos(theta)
		+ genten.y * (1 - cos(theta)) - genten.x * sin(theta);
}

static t_point	change(t_point p, t_move *move, t_map *map)
{
	double	_x;
	double	_y;
	double	_z;

	_x = p.x;
	_y = p.y;
	_z = move->altitude * move->altitude * move->altitude
		* move->altitude * map->map[p.y * map->width + p.x];
	calc_rotate(&_x, &_y, move->z_theta,
		(t_point){map->width / 2, map->height / 2, 0});
	calc_rotate(&_x, &_z, move->y_theta,
		(t_point){map->width / 2, 0, 0});
	calc_rotate(&_y, &_z, move->x_theta,
		(t_point){map->height / 2, 0, 0});
	_x *= move->zoom;
	_y *= move->zoom;
	_x += move->lr;
	_y += move->ud;
	return ((t_point){(int)_x, (int)_y, p.color});
}
