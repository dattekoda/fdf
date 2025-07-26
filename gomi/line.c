#include "libft.h"
#include "../minilibx_mac/mlx.h"
#include <stdbool.h>
#include <stdio.h>

// #define ESC_KEY 65307
// #define UP_KEY 65362
// #define DOWN_KEY 65364
// #define RIGHT_KEY 65363
// #define LEFT_KEY 65361
// #define Q_KEY 113
// #define W_KEY 119
// #define A_KEY 97
// #define S_KEY 115
// #define D_KEY 100
// #define Z_KEY 122

// macos_key
#define ESC_KEY 53
#define UP_KEY 126
#define DOWN_KEY 125
#define RIGHT_KEY 124
#define LEFT_KEY 123
#define Q_KEY 12
#define W_KEY 13
#define A_KEY 0
#define S_KEY 1
#define D_KEY 2
#define Z_KEY 6

#define ERR 1
#define SUCCESS 0

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700

#define RED_COLOR 0xFF0000
#define GREEN_COLOR 0x00FF00
#define BLUE_COLOR 0x0000FF
#define WH_COLOR 0xFFFFFF

#ifndef KeyPress
# define KeyPress 2
#endif
#ifndef KeyPressMask
# define KeyPressMask 1L<<0
#endif

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
	t_img	*img;
}	t_data;

void	img_put_pix(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	slope_less_than_one(t_img *img, t_point d, t_point *a, int color)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * d.y - d.x;
	img_put_pix(img, a->x, a->y, color);
	while (i < d.x) {
		a->x += 1;
		if (p < 0)
			p = p + 2 * d.y;
		else {
			a->y += 1;
			p = p + 2 * d.y - 2 * d.x;
		}
		img_put_pix(img, a->x, a->y, color);
		i++;
	}
}

void	slope_bigger_than_one(t_img *img, t_point d, t_point *a, int color)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * d.x - d.y;
	img_put_pix(img, a->x, a->y, color);
	while (i < d.y)
	{
		a->y += 1;
		if (p < 0)
			p = p + 2 * d.x;
		else
		{
			a->x += 1;
			p = p + 2 * d.x - 2 * d.y;
		}
		img_put_pix(img, a->x, a->y, color);
		i++;
	}
}

void	set_start_goal(t_point *a, t_point *b, t_point *start, t_point *goal)
{
	if (a->x < b->x)
	{
		start->x = a->x;
		start->y = a->y;
		goal->x = b->x;
		goal->y = b->y;
	}
	else
	{
		start->x = b->x;
		start->y = b->y;
		goal->x = a->x;
		goal->y = a->y;
	}
}

void	render_line(t_img *img, t_point *a, t_point *b, int color)
{
	int	dx;
	int	dy;
	t_point	start;
	t_point goal;

	set_start_goal(a, b, &start, &goal);
	dx = ft_abs(goal.x - start.x);
	dy = ft_abs(goal.y - start.y);
	if (dx > dy)
		slope_bigger_than_one(img, (t_point){dx, dy}, &start, color);
	else
		slope_less_than_one(img, (t_point){dx, dy}, &start, color);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		j = -1;
		while (++j < WINDOW_WIDTH)
			img_put_pix(img, j, i, color);
	}
}

int	render(t_data *data)
{
	if (!data->win_ptr)
		return (ERR);
	render_background(data->img, BLUE_COLOR);
	render_line(data->img, &(t_point){30, 30}, &(t_point){700, 100}, WH_COLOR);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img, 0, 0);
	return (SUCCESS);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == ESC_KEY)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (SUCCESS);
}

int	main(void)
{
	t_data	data;
	t_img	img;

	data.img = &img;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (ERR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "window");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), ERR);
	img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp,
			&img.line_len, &img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, img.mlx_img);
	// mlx_destroy_display(data.mlx_ptr);
	return (free(data.mlx_ptr), SUCCESS);
}
