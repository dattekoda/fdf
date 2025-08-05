#ifndef MAP_H
# define MAP_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# define ELEMSET "0123456789abcdef"

# include "../jikken.h"
# include <stdio.h>
# include <fcntl.h>

void	free_split(char **sp);
int		count_elems(char **sp);
void	free_map(t_map *map);
int		hex(char *str, char *elem);

#endif