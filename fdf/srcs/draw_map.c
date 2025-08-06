/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:29:24 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/06 14:49:43 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static 		t_point	change(t_point p, t_move *move, t_map *map);
static void	calc_rotate(double *a, double *b, double theta, t_point genten);
static int	calc_isometric(t_map *map, t_move *move);

int	draw_map(t_img *img, t_map *map, t_move *move)
{
	int	x;
	int	y;
	int	idx;

	y = -1;
	if (calc_isometric(map, move))
		return (1);
	while (++y < map->height - 1)
	{
		x = -1;
		while (++x < map->width - 1)
		{
			idx = y * map->width + x;
			draw_line(img, map->isom_map[idx], map->isom_map[idx + 1]);
			draw_line(img, map->isom_map[idx], map->isom_map[idx + map->width]);
		}
	}
	return (0);
}

static int	calc_isometric(t_map *map, t_move *move)
{
	int		x;
	int		y;
	int		*col;
	t_point	*isom;

	map->isom_map = malloc(sizeof(t_point) * map->height * map->width);
	if (!map->isom_map)
		return (1);
	y = -1;
	col = map->map_color;
	isom = map->isom_map;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
			*(isom++) = change((t_point){x, y, *(col++)}, move, map);
	}
	return (0);
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
