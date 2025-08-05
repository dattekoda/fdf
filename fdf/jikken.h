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
#define E_KEY 14
#define W_KEY 13
#define A_KEY 0
#define S_KEY 1
#define D_KEY 2
#define I_KEY 34
#define X_KEY 7
#define Y_KEY 16
#define Z_KEY 6
#define PLUS_KEY 24
#define MINUS_KEY 27
#define COMMA_KEY 43 // <
#define DOT_KEY 47 // >

// color
#define RED_COLOR 0x00FF0000
#define GREEN_COLOR 0x0000FF00
#define BLUE_COLOR 0x000000FF
#define WH_COLOR 0x00FFFFFF
#define BACK_GROUND 0x00000000

#define ERR 1
#define SUCCESS 0

#define WINDOW_TITLE "fdf"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define THETA_DEFAULT 0.42
#define ZOOM_DEFAULT 3000
#define DELTA_THETA 0.03
#define DELTA_ALTITUDE 0.002
#define DELTA_ZOOM 2
#define DELTA_LR 4
#define DELTA_UD 4

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
	int	color;
}	t_point;

typedef struct s_line
{
	t_point *s;
	t_point *g;
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
	int		*map;
	int		*map_color;
}	t_map;

typedef struct s_move
{
	double	x_theta;
	double	y_theta;
	double	z_theta;
	double	altitude;
	int		zoom;
	int		lr;
	int		ud;
}	t_move;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	char	**argv;
	t_map	*map;
	t_move	*move;
}	t_data;

// keypress.c
void	move_camera(int keysym, t_data *data);
void	rotate_camera(int keysym, t_data *data);
void	change_map(int keysym, t_data *data);

// color.c
int		calc_color(t_line *line, t_point current, bool big);

// free.c
void	free_fdf(t_data	*data);

// put_pix.c
void	img_put_pix(t_img *img, int x, int y, int color);

// line.c
void	draw_line(t_img *img, t_point a, t_point b);

// parse/validate_map.c
int		validate_map(char *file, t_map *map);
void	free_map(t_map *map);

// draw_map.c
void	draw_map(t_img *img, t_map *map, t_move *move);

// set.c
int		set_data(t_data *data, char *file);
t_move	set_move(t_map *map);

#endif