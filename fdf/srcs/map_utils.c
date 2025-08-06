/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:57:58 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/06 17:01:11 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	count_elems(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (*line && *line == ' ')
			line++;
		if (!*line)
			break ;
		count++;
		while (*line && *line != ' ')
			line++;
	}
	return (count);
}

void	free_map(t_map *map)
{
	if (map->map)
		free(map->map);
	if (map->map_color)
		free(map->map_color);
}

// str = "0x00ff00", assume there should be starting from 0x
// elem = "0123456789abcdef" = ELEMSET
// if elem is invalid then return -1
int	hex(char *str, char *elem)
{
	int		hex;
	char	*tmp;

	if (!str)
		return (-1);
	hex = 0;
	tmp = ft_strchr(str, 'x');
	if (!tmp)
		return (WH_COLOR);
	str = tmp + 1;
	while (*str && *str != ' ' && *str != '\n')
	{
		tmp = ft_strchr(elem, ft_tolower(*str++));
		if (!tmp)
			return (-1);
		hex = 16 * hex + (int)(tmp - elem);
	}
	return (hex);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	if (argc != 1)
// 		printf("%d", hex(argv[1], "0123456789abcdef"));
// }
