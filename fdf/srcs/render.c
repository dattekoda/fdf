/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:54:55 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/06 03:15:12 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "keypress.h"

static void		draw_background(t_img *img, int color);
static int		render(t_data *data);
static int		handle_keypress(int keysym, t_data *data);

void	img_put_pix(t_img *img, int x, int y, int color)
{
	int		i;

	if (0 <= x && x < WINDOW_WIDTH && 0 <= y && y < WINDOW_HEIGHT)
	{
		i = (x * img->bpp / 8) + (y * img->line_len);
		img->addr[i] = color;
		img->addr[++i] = color >> 8;
		img->addr[++i] = color >> 16;
	}
}

void	fdf(t_data *data)
{
	render(data);
	mlx_hook(data->win_ptr, KEYPRESS, KEYPRESSMASK, &handle_keypress, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	// mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

static void	draw_background(t_img *img, int color)
{
	int	i;
	int	*image;

	i = -1;
	image = (int *)img->addr;
	while (++i < WINDOW_HEIGHT * WINDOW_WIDTH)
		image[i] = color;
}

static int	render(t_data *data)
{
	draw_background(data->img, BACK_GROUND);
	draw_map(data->img, data->map, data->move);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img->mlx_img, 0, 0);
	return (SUCCESS);
}

static int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == ESC_KEY)
		exit((free_fdf(data), 0));
	if (keysym == UP_KEY || keysym == DOWN_KEY
		|| keysym == LEFT_KEY || keysym == RIGHT_KEY
		|| keysym == PLUS_KEY || keysym == MINUS_KEY)
		move_camera(keysym, data);
	else if (keysym == A_KEY || keysym == D_KEY
		|| keysym == W_KEY || keysym == S_KEY
		|| keysym == Q_KEY || keysym == E_KEY
		|| keysym == I_KEY || keysym == X_KEY
		|| keysym == Y_KEY || keysym == Z_KEY)
		rotate_camera(keysym, data);
	else if (keysym == DOT_KEY || keysym == COMMA_KEY)
		change_map(keysym, data);
	render(data);
	return (SUCCESS);
}
