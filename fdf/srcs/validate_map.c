/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:54:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/07 23:05:06 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	read_file(t_list **lst, char *file, t_map *map);
static int	check_validate(t_list *lst, t_map *map);
static void	get_one_line(t_map *map, char *line, int y);
static int	get_map(t_map *map, t_list *lst);

int	validate_map(char *file, t_map *map)
{
	t_list		*lst;

	map->height = 0;
	lst = NULL;
	if (read_file(&lst, file, map))
		return (ERR);
	if (check_validate(lst, map))
		return (ft_putendl_fd("Invalid map.", STDERR_FILENO),
			ft_lstclear(&lst, free), ERR);
	if (get_map(map, lst))
		return (ft_lstclear(&lst, free), ERR);
	ft_lstclear(&lst, free);
	return (SUCCESS);
}

static int	read_file(t_list **lst, char *file, t_map *map)
{
	int		gnl;
	int		fd;
	char	*line;

	gnl = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror(file), ERR);
	while (gnl > 0)
	{
		gnl = ft_get_next_line(fd, &line);
		if (gnl < 0)
			return (close(fd), ft_lstclear(lst, free), ERR);
		if (!*line)
		{
			free(line);
			break ;
		}
		ft_lstadd_back(lst, ft_lstnew(line));
		(map->height)++;
	}
	map->width = count_elems((*lst)->content);
	return (close(fd), SUCCESS);
}

static int	check_validate(t_list *lst, t_map *map)
{
	int		width;
	int		i;
	t_list	*n;

	i = -1;
	n = lst;
	if (map->height == 0)
		return (ERR);
	while (++i < map->height)
	{
		width = count_elems(n->content);
		if (width != map->width)
			return (ERR);
		n = n->next;
	}
	return (SUCCESS);
}

static void	get_one_line(t_map *map, char *line, int y)
{
	int		x;
	int		idx;
	char	*elem;
	char	*tmp;

	x = -1;
	elem = line;
	while (elem && *elem)
	{
		while (*elem && *elem == ' ')
			elem++;
		if (!*elem || *elem == '\n')
			break ;
		idx = y * map->width + (++x);
		map->map[idx] = ft_atoi(elem);
		map->map_color[idx] = LINE_COLOR;
		tmp = ft_strchr(elem, ',');
		elem = ft_strchr(elem, ' ');
		if (tmp && ((elem && tmp < elem) || !elem))
			map->map_color[idx] = hex(tmp + 1, ELEMSET);
	}
}

static int	get_map(t_map *map, t_list *lst)
{
	int		y;
	t_list	*n;

	map->map = (int *)malloc(sizeof(int) * map->height * map->width);
	map->map_color = (int *)malloc(sizeof(int) * map->height * map->width);
	if (!map->map || !map->map_color)
		return (free_map(map), ERR);
	y = -1;
	n = lst;
	while (++y < map->height)
	{
		get_one_line(map, n->content, y);
		n = n->next;
	}
	return (SUCCESS);
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
// 	printf("width: %d\n", map.width);
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
