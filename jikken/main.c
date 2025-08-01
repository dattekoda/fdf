#include "jikken.h"

void	draw_background(t_img *img, int color)
{
	int	i;
	int	*image;

	i = -1;
	ft_bzero(img->addr, WINDOW_HEIGHT * WINDOW_WIDTH * (img->bpp / 8));
	image = (int *)img->addr;
	while (++i < WINDOW_HEIGHT * WINDOW_WIDTH)
		image[i] = color;
}

int	render(t_data *data)
{
	if (!data->win_ptr)
		return (ERR);
	draw_background(data->img, BACK_GROUND);
	draw_map(data->img, data->map, WH_COLOR);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img->mlx_img, 0, 0);
	return (SUCCESS);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == ESC_KEY)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		exit(0);
	}
	// if (keysym == LEFT_KEY)
	// {
	// 	mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	// }
	return (SUCCESS);
}

t_move	set_move(void)
{
	t_move	move;

	move.theta = THETA_DEFAULT;
	move.zoom = ZOOM_DEFAULT;
	move.lr = WINDOW_WIDTH / 2;
	move.ud = WINDOW_HEIGHT / 2;
	return (move);
}

t_delta	set_delta(void)
{
	t_delta	delta;

	delta.theta = DELTA_THETA;
	delta.zoom = DELTA_ZOOM;
	delta.lr = DELTA_LR;
	delta.ud = DELTA_UD;
	return (delta);
}

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
	*(data->move) = set_move();
	*(data->delta) = set_delta();
	return (0);
}

void	fdf(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	// mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_img	*img;
	t_map	map;
	t_move	move;
	t_delta	delta;

	if (argc != 2 || !(data = (t_data *)ft_calloc(1, sizeof(t_data))))
		return (1);
	if (!(img = (t_img *)ft_calloc(1, sizeof(t_img))))
		return (free(data), 1);
	data->img = img;
	data->map = &map;
	data->move = &move;
	data->delta = &delta;
	if (set_data(data, argv[1]))
		return (free(data), free(img), 1);
	fdf(data);
	return (free(data), free_map(&map), 0);
}
