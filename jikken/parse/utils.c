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
	int	i;

	i = -1;
	while (++i < map->height)
		free(map->map[i]);
	free(map->map);
}