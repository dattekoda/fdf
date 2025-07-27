#include "jikken.h"

static t_point	change(t_point p, int zoom, double theta, t_map *map);

void	draw_map(t_img *img, t_map *map, int color)
{
	int		x;
	int		y;
	int		zoom;
	double	theta;
	t_point	start;

	zoom = 20;
	theta = 0.45;
	y = -1;
	while (++y < map->height - 1)
	{
		x = -1;
		while (++x < map->width - 1)
		{
			start = change((t_point){x, y}, zoom, theta, map);
			draw_line(img, start
				, change((t_point){x + 1, y}, zoom, theta, map) , color);
			draw_line(img, start
				, change((t_point){x, y + 1}, zoom, theta, map) , color);
		}
	}
}

static t_point	change(t_point p, int zoom, double theta, t_map *map)
{
	double	_x;
	double	_y;

	_x = (p.x - p.y) * cos(theta);
	_y = (p.x + p.y) * sin(theta) - map->map[p.y][p.x];
	_x *= zoom;
	_y *= zoom;
	_x += WINDOW_WIDTH / 2;
	_y += WINDOW_HEIGHT / 2;
	return ((t_point){(int)_x, (int)_y});
}
