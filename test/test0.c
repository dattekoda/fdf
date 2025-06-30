#include "test.h"

int	main(void)
{
	t_data	data;
	size_t	x_len = 601;
	size_t	y_len = 301;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), MLX_ERROR);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data.img.mlx_img)
		return (free(data.mlx_ptr), free(data.win_ptr), MLX_ERROR);
	while (x_len-- != 0)
		while (y_len-- != 0)
			mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, x_len, y_len);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}