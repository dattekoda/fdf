#ifndef TEST_H
# define TEST_H
# define _USE_MATH_DEFINES
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdint.h>
# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"
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

typedef struct s_cir
{
	int	x;
	int	y;
	int	radius;
	int	thickness;
	int	color;
}	t_cir;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; //bits per pixel
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_line
{
	int	s_x;
	int	s_y;
	int	g_x;
	int	g_y;
}	t_line;

typedef struct s_int_list
{
	int		**list;
	size_t	x;
	size_t	y;
}	t_int_list;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_int_list	*list;
}	t_data;

#endif