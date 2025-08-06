/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:54:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/06 13:27:31 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	read_file(t_list **lst, size_t *len, char *file, t_map *map);
static int	get_str_map(char *file, t_map *map, char **str_map);
static int	get_map(t_map *map, char **sp_map);

int	validate_map(char *file, t_map *map)
{
	char		*str_map;
	char		**sp_map;

	map->height = 0;
	if (get_str_map(file, map, &str_map))
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

static int	read_file(t_list **lst, size_t *len, char *file, t_map *map)
{
	int		gnl;
	int		fd;
	char	*line;

	gnl = 1;
	*len = 0;
	*lst = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror(file), 1);
	while (gnl > 0)
	{
		gnl = ft_get_next_line(fd, &line);
		if (gnl < 0)
			return (close(fd), ft_lstclear(lst, free), 1);
		if (!*line)
		{
			free(line);
			break ;
		}
		ft_lstadd_back(lst, ft_lstnew(line));
		*len += ft_strlen(line) + 1;
		(map->height)++;
	}
	return (close(fd), 0);
}

static int	get_str_map(char *file, t_map *map, char **str_map)
{
	char	*_str_map;
	size_t	len;
	t_list	*lst;
	t_list	*n;

	if (read_file(&lst, &len, file, map))
		return (1);
	*str_map = malloc(len + 1);
	if (!*str_map)
		return (ft_lstclear(&lst, free), 1);
	_str_map = *str_map;
	n = lst;
	while (n)
	{
		len = ft_strlen(n->content);
		ft_memcpy(_str_map, n->content, len);
		_str_map += len;
		*_str_map++ = ' ';
		n = n->next;
	}
	*_str_map = '\0';
	return (ft_lstclear(&lst, free), 0);
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
// 	printf("height: %d\n", map.height);
// 	// y = -1;
// 	// while (++y < map.height)
// 	// {
// 	// 	x = -1;
// 	// 	while (++x < map.width)
// 	// 		printf("%d ", map.map_color[y * map.width + x]);
// 	// 	printf("\n");
// 	// }
// 	free_map(&map);
// 	return (0);
// }
