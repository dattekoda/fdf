/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 03:05:14 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/06 03:05:15 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define ELEMSET "0123456789abcdef"

# include "utils.h"
# include <stdio.h>
# include <fcntl.h>

void	free_split(char **sp);
int		count_elems(char **sp);
void	free_map(t_map *map);
int		hex(char *str, char *elem);

#endif