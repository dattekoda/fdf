#include "libft.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>

// linux
#define ESC_KEY 65307
#define UP_KEY 65362
#define DOWN_KEY 65364
#define RIGHT_KEY 65363
#define LEFT_KEY 65361
#define Q_KEY 113
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define Z_KEY 122
#define RED_COLOR 0x00FF0000
#define GREEN_COLOR 0x0000FF00
#define BLUE_COLOR 0x000000FF
#define WH_COLOR 0x00FFFFFF

// macos_key
// #define ESC_KEY 53
// #define UP_KEY 126
// #define DOWN_KEY 125
// #define RIGHT_KEY 124
// #define LEFT_KEY 123
// #define Q_KEY 12
// #define W_KEY 13
// #define A_KEY 0
// #define S_KEY 1
// #define D_KEY 2
// #define Z_KEY 6
// #define RED_COLOR 0x00FF0000
// #define GREEN_COLOR 0x0000FF00
// #define BLUE_COLOR 0x000000FF
// #define WH_COLOR 0x00FFFFFF

#define ERR 1
#define SUCCESS 0

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 675

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

typedef struct s_line
{
	t_point *a;
	t_point *b;
	t_point *d;
}	t_line;


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
	char	**argv;
}	t_data;

void	img_put_pix(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || WINDOW_WIDTH < x || y < 0 || WINDOW_HEIGHT < y)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	if (img->endian) // big endian
	{
		pixel[0] = (color >> 24) & 0xFF; //A
		pixel[1] = (color >> 16) & 0xFF; //R
		pixel[2] = (color >> 8) & 0xFF; //G
		pixel[3] = color & 0xFF; //B
		return ;
	}
	// little endian
	pixel[0] = color & 0xFF; //B
	pixel[1] = (color >> 8) & 0xFF; //G
	pixel[2] = (color >> 16) & 0xFF; //R
	pixel[3] = (color >> 24) & 0xFF; //A
}

void	render_horizontal_vertical(t_img *img, t_line *line, int color)
{
	int		start;
	int		goal;
	int		unchanged;

	if (line->a->y - line->b->y == 0) //horizontal
	{
		start = ft_min(line->a->x, line->b->x);
		goal = ft_max(line->a->x, line->b->x);
		unchanged = line->a->y;
		while (start <= goal)
			img_put_pix(img, start++, unchanged, color);
		return ;
	}
	start = ft_min(line->a->y, line->b->y);//vertical
	goal = ft_max(line->a->y, line->b->y);
	unchanged = line->a->x;
	while (start <= goal)
		img_put_pix(img, unchanged, start++, color);
}

void	render_bigger_than_one(t_img *img, t_line *line, int color)
{
	int		p;
	int		append;
	t_point	*tmp;

	if (line->b->y == ft_min(line->a->y, line->b->y))
	{
		tmp = line->a;
		line->a = line->b;
		line->b = tmp;
	}
	append = 1;
	if (line->b->x - line->a->x < 0)
		append = -1;
	p = 2 * line->d->x - line->d->y;
	while (line->a->y <= line->b->y)
	{
		img_put_pix(img, line->a->x, (line->a->y)++, color);
		if (p < 0)
			p += 2 * line->d->x;
		else
		{
			p += 2 * line->d->x - 2 * line->d->y;
			line->a->x += append;
		}
	}
}

void	render_less_than_one(t_img *img, t_line *line, int color)
{
	int		p;
	int		append;
	t_point	*tmp;

	if (line->b->x == ft_min(line->a->x, line->b->x))
	{
		tmp = line->a;
		line->a = line->b;
		line->b = tmp;
	}
	append = 1;
	if (line->b->y - line->a->y < 0)
		append = -1;
	p = 2 * line->d->y - line->d->x;
	while (line->a->x <= line->b->x)
	{
		img_put_pix(img, (line->a->x)++, line->a->y, color);
		if (p < 0)
			p += 2 * line->d->y;
		else
		{
			p += 2 * line->d->y - 2 * line->d->x;
			line->a->y += append;
		}
	}
}

void	render_line(t_img *img, t_point a, t_point b, int color)
{
	t_line	line;
	t_point	d;

	d.x = ft_abs(a.x - b.x);
	d.y = ft_abs(a.y - b.y);
	line.d = &d;
	line.a = &a;
	line.b = &b;
	if (d.y == 0 || d.x == 0)
		render_horizontal_vertical(img, &line, color);
	else if (d.y > d.x)
		render_bigger_than_one(img, &line, color);
	else
		render_less_than_one(img, &line, color);
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
	render_line(data->img, (t_point){ft_atoi(data->argv[1]), ft_atoi(data->argv[2])}
			, (t_point){ft_atoi(data->argv[3]), ft_atoi(data->argv[4])}, WH_COLOR);
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
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;

	if (argc != 5)
		return (1);
	data.img = &img;
	data.argv = argv;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (ERR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "window");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), ERR);
	img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp,
			&img.line_len, &img.endian);
	// printf("bpp=%d line_len=%d endian=%d\n", img.bpp, img.line_len, img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	return (free(data.mlx_ptr), SUCCESS);
}
