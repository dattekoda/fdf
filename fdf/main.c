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
	draw_background(data->img, BACK_GROUND);
	draw_map(data->img, data->map, data->move);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img->mlx_img, 0, 0);
	return (SUCCESS);
}

int	handle_keypress(int keysym, t_data *data)
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

void	fdf(t_data *data)
{
	render(data);
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

	if (argc != 2 || !(data = (t_data *)ft_calloc(1, sizeof(t_data))))
		return (1);
	if (!(img = (t_img *)ft_calloc(1, sizeof(t_img))))
		return (free(data), 1);
	data->img = img;
	data->map = &map;
	data->move = &move;
	if (set_data(data, argv[1]))
		return (free(data), free(img), 1);
	fdf(data);
	return (free(data), free_map(&map), 1);
}
