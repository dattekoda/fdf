/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:47:09 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/09 10:24:14 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	set_data(t_data *data, char *file)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img->mlx_img = NULL;
	if (validate_map(file, data->map))
		return (free_fdf(data), ERR);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (free_fdf(data), ERR);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (!data->win_ptr)
		return (free_fdf(data), ERR);
	data->img->mlx_img = mlx_new_image(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img->mlx_img)
		return (free_fdf(data), ERR);
	data->img->addr = mlx_get_data_addr(data->img->mlx_img, &data->img->bpp,
			&data->img->line_len, &data->img->endian);
	if (!data->img->addr)
		return (free_fdf(data), ERR);
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
	move.zoom = ft_min(WINDOW_HEIGHT / map->height,
			WINDOW_WIDTH / map->width) / 2;
	move.lr = WINDOW_WIDTH / 2;
	move.ud = WINDOW_HEIGHT / 2;
	move.big_map = false;
	if (move.zoom < 10)
		move.big_map = true;
	return (move);
}
