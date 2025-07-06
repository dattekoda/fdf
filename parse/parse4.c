#include "../test/test.h"

char	*get_txt(int fd)
{
	char	*buf;
	char	*txt;
	char	*tmp;
	size_t	buf_size;
	ssize_t	n;

	txt = ft_strdup("");
	buf_size = 4096; //cpuが一回に読み込める最大量 getconf PAGE_SIZE
	while (txt)
	{
		buf = malloc(buf_size + 1);
		if (!buf)
			return (free(txt), NULL);
		n = read(fd, buf, buf_size);
		if (n < 0)
			return (free(txt), free(buf), NULL);
		else if (n == 0)
			return (free(buf), txt);
		buf[n] = '\0';
		tmp = txt;
		txt = ft_strjoin(tmp, buf);
		buf_size *= (free(tmp), free(buf), 2);
	}
	return (txt);
}

size_t	count_words(char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

size_t	count_line(char *txt)
{
	char	*_txt;

	_txt = txt;
	while (*_txt && *(_txt + 1))
		_txt++;
	if (*_txt == '\n')
		return (count_words(txt, '\n'));
	return (count_words(txt, '\n') + 1);
}

size_t	count_column(char *txt)
{
	size_t	count;

	count = 0;
	while (*txt && *txt != '\n')
	{
		while (*txt == ' ')
			txt++;
		if (!*txt || *txt == '\n')
			break ;
		count++;
		while (*txt && *txt != ' ' && *txt != '\n')
			txt++;
	}
	return (count);
}

int	have_color(char **elem)
{
	char	*confirm;
	char	*space_ptr;
	char	*nl_ptr;

	confirm = ft_strchr(*elem, ',');
	if (!confirm)
		return (0);
	space_ptr =ft_strchr(*elem, ' ');
	nl_ptr =ft_strchr(*elem, '\n');
	if ((space_ptr && confirm >= space_ptr) ||
		(nl_ptr && confirm >= nl_ptr))
		return (0);
	*elem = confirm + 3;
	return (1);
}

uint32_t	get_color(const char *elem, const char *base)
{
	uint32_t	num;
	size_t		base_len;
	char		*base_ptr;

	num = 0;
	base_len = ft_strlen(base);
	while (*elem && *elem != ' ' && *elem != '\n')
	{
		base_ptr = ft_strchr(base, ft_tolower(*elem++));
		if (!base_ptr)
			break ;
		num = num * base_len + (base_ptr - &base[0]);
	}
	return (num);
}

char	*get_elem(char *txt, int x, int y)
{
	char	*elem;

	elem = txt;
	while (y--)
	{
		elem = ft_strchr(elem, '\n');
		if (!elem)
			return (NULL);
		++elem;
	}
	while (*elem == ' ')
		elem++;
	while (x--)
	{
		elem = ft_strchr(elem, ' ');
		if (!elem || *elem == '\n')
			return (NULL);
		while (*elem == ' ')
			elem++;
	}
	return (elem);
}

void	free_map(t_map *map)
{
	size_t	i;
	size_t	y;

	y = map->y;
	i = -1;
	while (++i < map->y)
	{
		if (map->color[i])
			free(map->color[i]);
		if (map->list[i])
			free(map->list[i]);
	}
	free(map->color);
	free(map->list);
	free(map);
}

t_map	*init_map(char *txt)
{
	t_map	*map;
	size_t	i;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->y = count_line(txt);
	map->x = count_column(txt);
	map->list = malloc(sizeof(int *) * map->y);
	if (!map->list)
		return (free(map), NULL);
	map->color = malloc(sizeof(uint32_t *) * map->y);
	if (!map->color)
		return (free(map->list), free(map), NULL);
	i = -1;
	while (++i < map->y)
	{
		map->list[i] = malloc(sizeof(int) * map->x);
		map->color[i] = malloc(sizeof(int) * map->x);
		if (!map->color[i] || !map->list[i])
			return (free_map(map), NULL);
	}
	return (map);
}

int	get_map(t_data *data, char *txt)
{
	t_map	*map;
	size_t	x;
	size_t	y;
	char	*elem;

	map = init_map(txt);
	if (!map)
		return (FAILURE);
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			elem = get_elem(txt, x, y);
			map->list[y][x] = ft_atoi(elem);
			map->color[y][x] = 0x00FFFFFF;
			if (have_color(&elem))
				map->color[y][x] = get_color(elem, "0123456789abcdef");
		}
	}
	data->map = map;
	return (SUCCESS);
}

t_proj	**init_proj(t_data *data)
{
	t_proj	**proj;
	int		y;

	proj = malloc(data->map->y * sizeof(t_proj *));
	y = -1;
	while (proj && ++y < data->map->y)
	{
		proj[y] = malloc(data->map->x * sizeof(t_proj));
		if (!proj[y])
		{
			while (y-- > -1)
				free(proj[y]);
			return (free(proj), NULL);
		}
	}
	return (proj);
}

void	free_proj(t_proj **proj, t_map *map)
{
	int	y;

	y = -1;
	while (++y < map->y)
		free(proj[y]);
	free(proj);
}

int	get_proj(t_data *data)
{
	int	z;
	int	y;
	int	x;
	double	sx;
	double	sy;
	t_proj	**proj;

	proj = init_proj(data);
	if (!proj)
		return (FAILURE);
	y = -1;
	while (++y < data->map->y)
	{
		x = -1;
		while (++x < data->map->x)
		{
			z = data->map->list[y][x];
			sx = (x - y) * cos(data->cam.angle) * data->cam.zoom + data->cam.offset_x;
			sy = (x + y) * sin(data->cam.angle) * data->cam.zoom +
				z * data->cam.zoom + data->cam.offset_y;
			proj[y][x].x = (int)sx;
			proj[y][x].y = (int)sy;
 		}
	}
	data->proj = proj;
	data->changed = 0;
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	char	*txt;
	int		fd;
	int		y = -1;
	int		x;

	data.cam.angle = 0.4;
	data.cam.offset_x = WINDOW_WIDTH / 2;
	data.cam.offset_y = WINDOW_HEIGHT / 2;
	data.cam.zoom = 20;
	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	txt = get_txt(fd);
	if (!txt)
		return (FAILURE);
	if (get_map(&data, txt))
		return (free(txt), free_map(data.map), FAILURE);
	free(txt);
	if (get_proj(&data))
		return (free_proj(data.proj, data.map), free_map(data.map), FAILURE);
	while (++y < data.map->y)
	{
		x = -1;
		while (++x < data.map->x)
			printf("%2d,%2d: %d, %d\n", x, y, data.map->list[y][x], data.map->color[y][x]);
	}
	free_proj(data.proj, data.map);
	free_map(data.map);
	return (close(fd), 0);
}