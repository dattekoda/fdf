#include "test.h"

int	handle_keypress(int	keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	// if (keysym == XK_A)
	// {
	// 	描写を左にずらす。
	// }
	// if (keysym == XK_D)
	// {
	// 	描写を右にずらす。
	// }
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	render_point(t_img *img, int color)
{
	int	**fdf;
	int	size_x;
	int	size_y;

	size_x = 3;
	size_y = 2;
	fdf = ft_calloc(size_y, sizeof(int *));
	fdf[0] = ft_calloc(size_x, sizeof(int));
	fdf[1] = ft_calloc(size_x, sizeof(int));
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img, j++, i, color);
		++i;
	}
}

void	render_line(t_img *img, t_line line, t_color color)
{
	int	i;
	int	j;
	int	func;
	int	i_limit;
	int	j_limit;
	uint32_t	grad;
	uint32_t	delta;

	i = line.s_y < line.g_y ? line.s_y : line.g_y;
	i_limit = line.s_y < line.g_y ? line.g_y : line.s_y;
	j_limit = line.s_x < line.g_x ? line.g_x : line.s_x;
	grad = color.start;
	while (i <= i_limit)
	{
		j = line.s_x < line.g_x ? line.s_x : line.g_x;
		while (j <= j_limit)
		{
			func = (i - line.s_y) * (line.g_x - line.s_x) - (j - line.s_x) * (line.g_y - line.s_y);
			if (abs(func) < 300) //オーバーフローケアするように要修正。
				img_pix_put(img, j, i, grad);
			j++;
		}
		i++;
	}
}

int	render(t_data *data)
{
	if (!data->win_ptr)
		return (1);
	render_background(&data->img,BLU_PIXEL);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	//4th and 5th arguments indicate the starting position (coordinates).
	//Perhaps, you can use this as a zooming or moving functions.
	return (0);
}

int	show_screen(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "window");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), MLX_ERROR);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	return (free(data.mlx_ptr), 0);
}

int	main(void)
{
	return (show_screen());
}
