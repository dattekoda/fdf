#include "libft.h"
#include "mlx.h"
#include <stdio.h>

#define ERR 1
#define SUCCESS 0

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

typedef struct s_point
{
	int x;
	int y;
}	t_point;

typedef struct s_img
{
	void	*mlx_img;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int	main(void)
{
	t_data	data;
	t_img	img;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (ERR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "window");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), ERR);
	img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(data.mlx_ptr, &img.bpp,
			&img.line_len, &img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &hendle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	return (free(data.mlx_ptr), SUCCESS);
}

void	slope_less_than_one(int dx, int dy, t_point *a)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * dy - dx;
	put_pixel(a->x, a->y);
	while (i < dx) {
		a->x += 1;
		if (p < 0)
			p = p + 2 * dy;
		else {
			a->y += 1;
			p = p + 2 * dy - 2 * dx;
		}
		put_pixel(a->x, a->y);
		i++;
	}
}

void	slope_bigger_than_one(int dx, int dy, t_point *a)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * dx - dy;
	put_pixel(a->x, a->y);
	while (i < dy)
	{
		a->y += 1;
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			a->x += 1;
			p = p + 2 *dx - 2 * dy;
		}
		put_pixel(a->x, a->y);
		i++;
	}
}

int	drawing_line(t_img *img)
{
	int	dx;
	int	dy;
	t_point	a = {0, 0};
	t_point b = {732, 25};

	dx = ft_abs(b.x - a.x);
	dy = ft_abs(a.y - b.y);
}