/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:31:40 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/07 14:30:38 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;
	t_map	map;
	t_move	move;

	if (argc != 2)
		return (ft_putendl_fd("Invalid number of arguments.",
				STDERR_FILENO), ERR);
	data.img = &img;
	data.map = &map;
	data.move = &move;
	if (set_data(&data, argv[1]))
		return (ft_putendl_fd("set.c", STDERR_FILENO), ERR);
	fdf(&data);
	return (free_map(&map), free(map.isom_map), ERR);
}
