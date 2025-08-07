/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 03:05:05 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/07 14:24:36 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include "libft.h"
# include "mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

// color
# define WH_COLOR 0x00FFFFFF
# define LINE_COLOR 0x00FFFFFF
# define BACK_GROUND 0x00444444

# define ERR 1
# define SUCCESS 0
# define WINDOW_TITLE "fdf"
# define WINDOW_WIDTH 1900
# define WINDOW_HEIGHT 1000
# define THETA_DEFAULT 0.42

# define PRESSWINDOW 17
# define KEYPRESS 2
# define KEYPRESSMASK 1L

# define DELTA_THETA 0.01
# define DELTA_ALTITUDE 0.002
# define DELTA_ZOOM 1
# define DELTA_LR 4
# define DELTA_UD 4

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

typedef struct s_line
{
	t_point	*s;
	t_point	*g;
	t_point	*d;
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
	t_point	*isom_map;
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
	bool	big_map;
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

// color.c
int		calc_color(t_line *line, t_point current, bool big);

// free.c
void	free_fdf(t_data	*data);

// keypress.c
int		handle_xpress(t_data *data);
int		handle_keypress(int keysym, t_data *data);

// render.c
void	img_put_pix(t_img *img, int x, int y, int color);
void	fdf(t_data *data);
int		render(t_data *data);

// line.c
void	draw_line(t_img *img, t_point a, t_point b);

// parse/validate_map.c
int		validate_map(char *file, t_map *map);
void	free_map(t_map *map);

// draw_map.c
int		draw_map(t_img *img, t_map *map, t_move *move);

// set.c
int		set_data(t_data *data, char *file);
t_move	set_move(t_map *map);

#endif