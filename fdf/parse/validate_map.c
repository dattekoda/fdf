/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:54:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/05 07:01:54 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror(file), 1);
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
	int		x;
	int		y;
	int		idx;
	char	*tmp;

	map->map = (int *)malloc(sizeof(int) * map->width * map->height);
	map->map_color = (int *)malloc(sizeof(int) * map->width * map->height);
	if (!map->map || !map->map_color)
		return (free_map(map), free_split(sp_map), 1);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			idx = y * map->width + x;
			tmp = sp_map[idx];
			map->map[idx] = ft_atoi(tmp);
			map->map_color[idx] = WH_COLOR;
			tmp = ft_strchr(tmp, ',');
			if (tmp)
				map->map_color[idx] = hex(tmp + 1, ELEMSET);
		}
	}
	return (free_split(sp_map), 0);
}

// int	main(int argc, char **argv)
// {
// 	t_map	map;
// 	int		x;
// 	int		y;

// 	if (argc != 2)
// 		return (1);
// 	if (validate_map(argv[1], &map))
// 		return (1);
// 	y = -1;
// 	while (++y < map.height)
// 	{
// 		x = -1;
// 		while (++x < map.width)
// 			printf("%d ", map.map[y * map.width + x]);
// 		printf("\n");
// 	}
// 	y = -1;
// 	while (++y < map.height)
// 	{
// 		x = -1;
// 		while (++x < map.width)
// 			printf("%d ", map.map_color[y * map.width + x]);
// 		printf("\n");
// 	}
// 	free_map(&map);
// 	return (0);
// }
