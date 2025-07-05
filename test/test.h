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
# define FAILURE 1
# define SUCCESS 0
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MLX_ERROR 1
# define RED_PIXEL 0xFF0000
# define GRE_PIXEL 0x00FF00
# define BLU_PIXEL 0x0000FF
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000

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

typedef struct s_square
{
	// int	grad;
	int	s_x;
	int	s_y;
	int	g_x;
	int	g_y;
}	t_square;

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

//because parse map left upper to right bottom.
typedef struct s_coords
{
	int				x;
	int				y;
	int				z;
	uint32_t		color;
	struct s_coords *right;
	struct s_coords *down;
}	t_coords;

typedef struct s_input
{
	char	*txt;
	size_t	num_l; //y
	size_t	num_c; //x
}	t_input;

char		*get_txt(int fd);
char		*get_elem(char *txt, int x, int y);
t_coords	*get_coordinate(t_input input, int i, int j);
t_coords	*get_all_coordinates(t_input input, int i, int j);
uint32_t	get_color(const char *elem, const char *base);
int			have_color(char **elem);
t_coords	*init_coords(int x, int y, char *elem);
size_t		count_words(char *s, char c);
size_t		count_line(char *txt);
size_t		count_column(char *txt);
int			check_coordinates(t_coords *coords, size_t num_l, size_t num_c);
void		free_coordinates(t_coords *coords);

#endif