/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:47:09 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/05 22:21:58 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jikken.h"
t_move	set_move(t_map *map);

int	set_data(t_data *data, char *file)
{
	if (!(data->mlx_ptr = mlx_init()))
		return (1);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)))
		return (free(data->mlx_ptr), 1);
	if (!(data->img->mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT)))
		return (free(data->mlx_ptr), 1);
	if (!(data->img->addr = mlx_get_data_addr(data->img->mlx_img, &data->img->bpp,
			&data->img->line_len, &data->img->endian)))
		return (mlx_destroy_image(data->mlx_ptr, data->img->mlx_img), free(data->mlx_ptr), 1);
	if (validate_map(file, data->map))
		return (mlx_destroy_image(data->mlx_ptr, data->img->mlx_img), free(data->mlx_ptr), 1);
	*(data->move) = set_move(data->map);
	return (0);
}

t_move	set_move(t_map *map)
{
	t_move	move;

	move.z_theta = THETA_DEFAULT;
	move.y_theta = 0;
	move.x_theta = THETA_DEFAULT * 2;
	move.altitude = 1;
	move.zoom = ft_min(WINDOW_WIDTH / map->width, WINDOW_HEIGHT / map->height) / 2;
	move.lr = WINDOW_WIDTH / 3;
	move.ud = WINDOW_HEIGHT / 3;
	return (move);
}
