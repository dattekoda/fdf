#include "../test/test.h"

size_t	split_len(char **split)
{
	size_t	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}

void	split_free(char **split)
{
	size_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

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

static size_t	count_words(const char *s, char c)
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

void	free_int_list(t_int_list *list, size_t point)
{
	size_t	i;

	i = -1;
	while (++i < point)
		free(list->list[i]);
	free(list->list);
	free(list);
}

t_int_list	*init_int_list(char *txt)
{
	t_int_list	*list;

	list = malloc(sizeof(t_int_list));
	list->y = count_words(txt, '\n');
	if (list->y == 0)
		return (free(list), NULL);
	list->x = count_words(txt, ' ') / list->y + 1;
	list->list = malloc(sizeof(int *) * list->x);
	if (!list)
		return (free(list), NULL);
	return (list);
}

t_int_list	*get_map(char *txt)
{
	t_int_list	*list;
	size_t	i;
	size_t	j;
	char	**row;
	char	**elems;

	list = init_int_list(txt);
	if (!list)
		return (NULL);
	row = ft_split(txt, '\n');
	if (!row)
		return (free(list->list), NULL);
	i = -1;
	while (++i < list->y)
	{
		elems = ft_split(row[i], ' ');
		if (!elems)
			return (free_int_list(list, i), split_free(row), NULL);
		list->list[i] = malloc(sizeof(int) * list->x);
		if (!list->list[i])
			return (free_int_list(list, i), split_free(row), split_free(elems), NULL);
		j = -1;
		while (++j < list->x)
			list->list[i][j] = ft_atoi(elems[j]);
		split_free(elems);
	}
	split_free(row);
	return (list);
}

t_coords	*init_coords(void)
{
	t_coords *coords;

	coords = malloc(sizeof(t_coords));
	if (!coords)
	return (NULL);
	coords->left = NULL;
	coords->up = NULL;
	coords->x = 0;
	coords->y = 0;
	coords->z = 0;
	return (coords);
}

//line = splited line char like ""0,0xFFFFFF", "1,0xFFFFFF""
// t_coords	*get_coordinates(char **line)
// {
// 	t_coords	*coords;
// 	static int	i = 0;

// 	coords = init_coords();
// 	if (!coords)
// 		return (NULL);
// 	if (i++)
// 	{
		
// 	}
// }

int	main(int argc, char *argv[])
{
	int			fd;
	char		*txt;
	t_int_list	*list;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	txt = get_txt(fd);
	close(fd);
	if (!txt)
		return (1);
	list = get_map(txt);
	free(txt);
	if (!list)
		return (1);
	return (free_int_list(list, list->y), 0);
}
