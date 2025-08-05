#include "map.h"

void	free_split(char **sp)
{
	char	**_sp;

	_sp = sp;
	while(*_sp)
		free(*_sp++);
	free(sp);
}

int	count_elems(char **sp)
{
	int	count;

	count = 0;
	while (*sp)
	{
		count++;
		sp++;
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
	str = ft_strchr(str, 'x') + 1;
	while (*str && *str != ' ')
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
