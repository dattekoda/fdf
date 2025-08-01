#include "map.h"

static char	*map_join(char *s1, char *s2);
static char	*get_str_map(int fd, t_map *map);
static int	get_map(t_map *map, char **sp_map);

int	validate_map(char *file, t_map *map)
{
	int			fd;
	char		*str_map;
	char		**sp_map;

	map->height = 0;
	map->width = 0;
	fd = open(file, O_RDONLY);
	str_map = get_str_map(fd, map);
	close(fd);
	if (!str_map)
		return (1);
	sp_map = ft_split(str_map, ' ');
	free(str_map);
	if (!sp_map)
		return (1);
	map->width = count_elems(sp_map) / map->height;
	if (get_map(map, sp_map))
		return (1);
	free_split(sp_map);
	return (0);
}

static char	*map_join(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = malloc(s1_len + s2_len + 1);
	if (!join)
		return (NULL);
	join[s1_len + s2_len] = '\0';
	if (s2[s2_len - 1] == '\n')
		join[s1_len + --s2_len] = ' ';
	while (s2_len-- != 0)
		join[s1_len + s2_len] = s2[s2_len];
	while (s1_len-- != 0)
		join[s1_len] = s1[s1_len];
	return (join);
}

static char	*get_str_map(int fd, t_map *map)
{
	int		gnl;
	char	*line;
	char	*str_map;
	char	*tmp;

	gnl = 1;
	str_map = ft_strdup("");
	if (!str_map)
		return (NULL);
	while (gnl > 0)
	{
		gnl = ft_get_next_line(fd, &line);
		if (gnl < 0)
			return (free(str_map), NULL);
		if (gnl == 0)
			break ;
		(map->height)++;
		tmp = str_map;
		str_map = map_join(str_map, line);
		if (!(free(line), free(tmp), map))
			return (NULL);
	}
	return (str_map);
}

static int	get_map(t_map *map, char **sp_map)
{
	int	y;
	int	x;

	map->map = (int **)malloc(sizeof(int *) * (map->height));
	if (!map->map)
		return (1);
	y = -1;
	while (++y < map->height)
	{
		map->map[y] = (int *)malloc(sizeof(int) * map->width);
		if (!map->map[y])
		{
			while (y-- != 0)
				free(map->map[y]);
			free(map->map);
			return (1);
		}
		x = -1;
		while (++x < map->width)
		{
			map->map[y][x] = ft_atoi(sp_map[y * map->width + x]);
			if (sp_map[y * map->width + x], ',')
	}
	return (0);
}

void	set_map(int	*map_map, char *map_col, char *sp)
{
	*map_map = ft_atoi(sp);
	if ((sp = ft_strchr(sp, ',')))
		map_col
}

// int	main(int argc, char **argv)
// {
// 	t_map	map;
// 	int		x;
// 	int		y;

// 	if (validate_map(argv[1], &map))
// 		return (1);
// 	y = -1;
// 	while (++y < map.height)
// 	{
// 		x = -1;
// 		while (++x < map.width)
// 			printf("%d ", map.map[y][x]);
// 		printf("\n");
// 	}
// 	free_map(&map);
// 	return (0);
// }
