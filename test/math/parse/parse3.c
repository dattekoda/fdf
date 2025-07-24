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

//各要素の先頭ポインタを取得
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

t_coords	*get_coordinate(t_input input, int x, int y)
{
	t_coords	*coords;
	char		*elem;

	coords = malloc(sizeof(t_coords));
	if (!coords)
		return (NULL);
	elem = get_elem(input.txt, x, y);
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

// int	main(void)
// {
// 	t_coords	*coords = get_coordinate((t_input){"0 0 100\n0 0 100\n0 0 5\n0 0 8", 0, 0}, 2, 0);
// 	printf("%4d, %4d, %4d\n", coords->x, coords->y, coords->z);
// }

t_coords	*get_behind_coordinate(t_input input, t_idx index, t_coords *r, t_coords *d)
{
	t_coords	*coords;

	coords = get_coordinate(input, index.x, index.y);
	coords->right = r;
	coords->down = d;
	if (index.x >= 0 && index.y >= 0)
	{
		get_behind_coordinate(input, (t_idx){index.x, index.y - 1}, r, coords);
		get_behind_coordinate(input, (t_idx){index.x - 1, index.y}, coords, d);
	}
	return (coords);
}

t_coords	*get_all_coordinates(t_input input)
{
	t_coords	*coords;

	coords = get_behind_coordinate(input, (t_idx){input.num_c - 1, input.num_l - 1}, NULL, NULL);
	return (coords);
}

int	main(void)
{
	t_coords	*coords;

	coords = get_all_coordinates((t_input){"2 3 7\n1 5 2\n8 9 4", 3, 3});
	return (0);
}

int	check_coordinates(t_coords *coords, size_t num_l, size_t num_c)
{
	t_coords	*_coords;
	size_t		checker_l;
	size_t		checker_c;

	checker_l = 0;
	while (coords)
	{
		_coords = coords;
		checker_c = 0;
		while (_coords)
		{
			printf("%2zu, %2zu, %2d, %2d, %2d\n", checker_c, checker_l, _coords->x, _coords->y, _coords->z);
			_coords = (checker_c++, _coords->right);
		}
		if (checker_c != num_c - 1)
			return (1);
		coords = (checker_l++, coords->down);
	}
	if (checker_l != num_l - 1)
		return (1);
	printf("checker ok\n");
	exit(1);
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
