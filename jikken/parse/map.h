#ifndef MAP_H
# define MAP_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include "../jikken.h"
# include <stdio.h>
# include <fcntl.h>

void	free_split(char **sp);
int		count_elems(char **sp);

#endif