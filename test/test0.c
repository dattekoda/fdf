#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "../minilibx/mlx.h"

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300
# define MLX_ERROR 1

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_data;

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
	data.img_ptr = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data.img_ptr)
		return (free(data.mlx_ptr), free(data.win_ptr), MLX_ERROR);
	while (x_len-- != 0)
		while (y_len-- != 0)
			mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, x_len, y_len);
	return (0);
}