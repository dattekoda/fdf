#ifndef TEST_H
# define TEST_H
# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdint.h>
# include "../minilibx/mlx.h"
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MLX_ERROR 1
# define RED_PIXEL 0xFF0000
# define GRE_PIXEL 0x00FF00
# define BLU_PIXEL 0x0000FF
# define WHITE_PIXEL 0xFFFFFF

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; //bits per pixel
	int		line_len;
	int		endian;
}	t_img;


typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

#endif