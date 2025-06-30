#include "test.h"

//uint8_t: An unsigned integer type of a fixed width of exactly N bits, N being the value specified
//in its type name. According to the C language standard, they shall be capable of stroring values
//in the range [0, UINTN_MAX], substituting N by the appropriate number.
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	render(t_data *data)
{
	int	i;
	int	j;
	int	range;

	i = 0;
	j = 0;
	range = 550;
	if (data->win_ptr)
	{
		while (j <= range)
		{
			i = 0;
			while (i <= range)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr,
					i++, j, GRE_PIXEL);
			j++;
		}
		j = WINDOW_HEIGHT;
		while (WINDOW_HEIGHT - range <= j)
		{
			i = WINDOW_WIDTH;
			while (WINDOW_WIDTH - range <= i)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr,
					i--, j, RED_PIXEL);
			j--;
		}
	}
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (!data.win_ptr)
		return (free(data.win_ptr), MLX_ERROR);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	return (free(data.mlx_ptr), 0);
}
