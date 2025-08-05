/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:40:04 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/05 22:44:37 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jikken.h"

void	free_fdf(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// mlx_destroy_display(data->mlx_ptr);
	if (data->map->map)
		free(data->map->map);
	if (data->map->map_color)
		free(data->map->map_color);
}