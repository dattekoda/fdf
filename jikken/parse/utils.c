// #include "map.h"

// void	free_split(char **sp)
// {
// 	char	**_sp;

// 	_sp = sp;
// 	while(*_sp)
// 		free(*_sp++);
// 	free(sp);
// }

// int	count_elems(char **sp)
// {
// 	int	count;

// 	count = 0;
// 	while (*sp)
// 	{
// 		count++;
// 		sp++;
// 	}
// 	return (count);
// }

// void	free_map(t_map *map)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < map->height)
// 		free(map->map[i]);
// 	free(map->map);
// }

#include <stdio.h>
#include "../libft/includes/libft.h"
// str = "0x00ff00", assume there should be starting from 0x
// elem = "0123456789abcdef"
int	hex(char *str, char *elem)
{
	int		hex;

	hex = 0;
	str = ft_strchr(str, 'x') + 1;
	while (*str)
	{
		hex = 16 * hex
			+ (int)(ft_strchr(elem, ft_tolower(*str++)) - elem);
	}
	return (hex);
}

int	main(void)
{
	printf("%d", hex("0x00000ff", "0123456789abcdef"));
}
