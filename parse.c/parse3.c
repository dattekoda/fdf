#include "../test/test.h"

char	*get_txt(int fd)
{
	char	*buf;
	size_t	buf_size;

	buf = NULL;
	buf_size = 4096; //cpuが一回に読み込める最大量 getconf PAGE_SIZE
	while (1)
	{
		buf = malloc(buf_size);
		if (!buf)
			break ;
		if (read(fd, buf, buf_size) == 0)
			break ;
		buf_size *= 2;
		free(buf);
	}
	return (buf);
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

int	have_color(char **elem)
{
	char	*confirm;
	char	*space_ptr;
	char	*new_line_ptr;

	confirm = ft_strchr(*elem, ',');
	space_ptr =ft_strchr(*elem, ' ');
	new_line_ptr =ft_strchr(*elem, '\n');
	if ((space_ptr && confirm >= space_ptr) ||
		(new_line_ptr && confirm >= new_line_ptr) ||
		confirm >= ft_strchr(*elem, '\0'))
		return (0);
	*elem = confirm + 3;
	return (1);
}

//各要素の先頭ポインタを取得
char	*get_elem(char *txt, int x, int y)
{
	char	*elem = txt;

	elem = txt;
	while (y--)
		elem = ft_strchr(elem, '\n') + 1;
	while (*elem == ' ')
		elem++;
	while (x--)
	{
		elem = ft_strchr(elem, ' ');
		while (*elem == ' ')
			elem++;
	}
	return (elem);
}

t_coords	*init_coords(int x, int y, char *elem)
{
	t_coords	*coords;

	coords = malloc(sizeof(t_coords));
	if (!coords)
	return (NULL);
	coords->right = NULL;
	coords->down = NULL;
	coords->x = x;
	coords->y = y;
	coords->z = ft_atoi(elem);
	coords->color = 0;
	if (have_color(&elem))
		coords->color = get_color(elem, "0123456789abcdef");
	return (coords);
}

t_coords	*get_coordinate(t_input input, int i, int j)
{
	t_coords	*coords;
	char		*elem;

	elem = get_elem(input.txt, i, j);
	coords = init_coords(i, j, elem);
	if (!coords)
		return (NULL);
	i = (i + 1) % input.num_c;
	if (i == 0)
		j++;
	return (coords);
}

static size_t	count_words(char *s, char c)
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

t_coords	*get_all_coordinates(t_input input, int i, int j)
{
	t_coords	*coords;

	coords = get_coordinate(input, i, j);
	if (coords && i + 1 != input.num_c)
		coords->right = get_all_coordinates(input, ++i, j);
	if (coords && j + 1 != input.num_l)
		coords->down = get_all_coordinates(input, i, ++j);
	return (coords);
}

int	check_coordinates(t_coords *coords, size_t num_l, size_t num_c)
{
	t_coords	*_coords;
	size_t		checker_l;
	size_t		checker_c;

	checker_l = 0;
	checker_c = 0;
	_coords = coords;
	while (coords)
	{
		checker_l = 0;
		while (_coords)
			coords = (checker_l++, coords->right);
		if (checker_l != num_l)
			return (1);
		coords = (checker_c++, coords->down);
		_coords = coords;
	}
	if (checker_c != num_c)
		return (1);
	return (0);
}

void	free_coordinates(t_coords *coords)
{
	t_coords	*coords_r;
	t_coords	*coords_d;

	coords_r = coords->right;
	coords_d = coords->down;
	free(coords);
	if (!coords_r)
		free_coordinates(coords_r);
	if (!coords_d)
		free_coordinates(coords_d);
}

int	main(int argc, char *argv[])
{
	t_coords	*coords;
	size_t		num_l;
	size_t		num_c;
	char		*txt;
	int			fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	txt = get_txt(fd);
	num_l = count_line(txt);
	num_c = count_column(txt);
	coords = get_all_coordinates((t_input){txt, num_l, num_c}, 0, 0);
	free(txt);
	if (check_coordinates(coords, num_l, num_c))
		return (close(fd), free_coordinates(coords), FAILURE);
	return (close(fd), free(coords), SUCCESS);
}
