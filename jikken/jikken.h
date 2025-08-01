#ifndef JIKKEN_H
#define JIKKEN_H

#include "libft.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>

// linux
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

// color
#define RED_COLOR 0x00FF0000
#define GREEN_COLOR 0x0000FF00
#define BLUE_COLOR 0x000000FF
#define WH_COLOR 0x00FFFFFF
#define BACK_GROUND 0x00555555

#define ERR 1
#define SUCCESS 0

#define WINDOW_TITLE "fdf"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define THETA_DEFAULT 0.42
#define ZOOM_DEFAULT 42
#define DELTA_THETA 0.03
#define DELTA_ZOOM 3
#define DELTA_LR 7
#define DELTA_UD 7

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
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	int		width;
	int		height;
	int		**map;
	char	**map_color;
}	t_map;

typedef struct s_move
{
	double	theta;
	int		zoom;
	int		lr;
	int		ud;
}	t_move;

typedef struct s_delta
{
	double	theta;
	int		zoom;
	int		lr;
	int		ud;
}	t_delta;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	char	**argv;
	t_map	*map;
	t_move	*move;
	t_delta	*delta;
}	t_data;

//put_pix.c
void	img_put_pix(t_img *img, int x, int y, int color);

//line.c
void	draw_line(t_img *img, t_point a, t_point b, int color);

//parse/validate_map.c
int		validate_map(char *file, t_map *map);
void	free_map(t_map *map);

//draw_map.c
void	draw_map(t_img *img, t_map *map, int color);

#endif