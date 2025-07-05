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
	coords->color = 0x00FFFFFF;
	if (have_color(&elem))
		coords->color = get_color(elem, "0123456789abcdef");
	return (coords);
}

t_coords	*get_coordinate(t_input input, int x, int y)
{
	t_coords	*coords;

	coords = init_coords(x, y, get_elem(input.txt, x, y));
	if (!coords)
		return (NULL);
	if (input.num_c != 0)
		x = (x + 1) % input.num_c;
	if (x == 0)
		y++;
	return (coords);
}

t_coords	*get_all_coordinates(t_input input, int x, int y)
{
	t_coords	*coords;

	coords = get_coordinate(input, x, y);
	if (!coords)
		return (NULL);
	if (coords && x + 1 < input.num_c)
		coords->right = get_all_coordinates(input, ++x, y);
	if (coords && y + 1 < input.num_l)
		coords->down = get_all_coordinates(input, x, ++y);
	return (coords);
}

int	check_coordinates(t_coords *coords, size_t num_l, size_t num_c)
{
	t_coords	*_coords;
	size_t		checker_l;
	size_t		checker_c;

	checker_l = 0;
	checker_c = 0;
	while (coords)
	{
		_coords = coords;
		checker_l = 0;
		while (_coords)
			_coords = (checker_c++, _coords->right);
		if (checker_c != num_c)
			return (1);
		coords = (checker_l++, coords->down);
	}
	if (checker_l != num_l)
		return (1);
	return (0);
}

void	free_coordinates(t_coords *coords)
{
	if (!coords)
		return ;
	free_coordinates(coords->right);
	free_coordinates(coords->down);
	free(coords);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	int		fd = open(argv[1], O_RDONLY);
	char	*txt = get_txt(fd);
	char	*elem;
	int		i, j;
	size_t	y, x;
	t_coords	*coords;

	i = -1;
	j = -1;
	x = count_column(txt);
	y = count_line(txt);
	coords = get_all_coordinates((t_input){txt, y, x}, 0, 0);
	// printf("%s\n", txt);
	// while (++j < y)
	// {
	// 	i = -1;
	// 	while (++i < x)
	// 	{
	// 		// elem = get_elem(txt, i, j);
	// 		// printf("%s\n", elem);
	// 		t_coords	*coords = get_coordinate((t_input){txt, y, x}, i, j);
	// 		// printf("(x, y) = (%2d, %2d) :%2d\n", i + 1, j + 1, ft_atoi(elem));
	// 	}
	// }
	free_coordinates(coords);
	free(txt);
	close(fd);
	return (0);
}