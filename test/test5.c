#include "test.h"


size_t	split_len(char **split)
{
	size_t	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}

void	split_free(char **split)
{
	size_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	*get_txt(int fd)
{
	char	*buf;
	size_t	buf_size;

	buf_size = 4096; //cpuが一回に読み込める最大量 getconf PAGE_SIZE
	while (1)
	{
		buf = malloc(buf_size);
		if (!buf)
			break ;
		if (read(fd, buf, buf_size) == 0)
			break ;
		buf_size *= 2;
		free(buf);
	}
	return (buf);
}

size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

void	free_int_list(t_map *list, size_t point)
{
	size_t	i;

	i = -1;
	while (++i < point)
		free(list->list[i]);
	free(list->list);
	free(list);
}

t_map	*init_map(char *txt)
{
	t_map	*list;

	list = malloc(sizeof(t_map));
	list->y = count_words(txt, '\n');
	if (list->y == 0)
		return (free(list), NULL);
	list->x = count_words(txt, ' ') / list->y + 1;
	list->list = malloc(sizeof(int *) * list->x);
	if (!list)
		return (free(list), NULL);
	return (list);
}

t_map	*get_map(char *txt)
{
	t_map	*list;
	size_t	i;
	size_t	j;
	char	**row;
	char	**elems;

	list = init_map(txt);
	if (!list)
		return (NULL);
	row = ft_split(txt, '\n');
	if (!row)
		return (free(list->list), NULL);
	i = -1;
	while (++i < list->y)
	{
		elems = ft_split(row[i], ' ');
		if (!elems)
			return (free_int_list(list, i), split_free(row), NULL);
		list->list[i] = malloc(sizeof(int) * list->x);
		if (!list->list[i])
			return (free_int_list(list, i), split_free(row), split_free(elems), NULL);
		j = -1;
		while (++j < list->x)
			list->list[i][j] = ft_atoi(elems[j]);
		split_free(elems);
	}
	split_free(row);
	return (list);
}

int	handle_keypress(int	keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	// if (keysym == XK_A)
	// {
	// 	描写を左にずらす。
	// }
	// if (keysym == XK_D)
	// {
	// 	描写を右にずらす。
	// }
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	render_point(t_img *img, int color)
{
	int	**fdf;
	int	size_x;
	int	size_y;

	size_x = 3;
	size_y = 2;
	fdf = ft_calloc(size_y, sizeof(int *));
	fdf[0] = ft_calloc(size_x, sizeof(int));
	fdf[1] = ft_calloc(size_x, sizeof(int));
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img, j++, i, color);
		++i;
	}
}

void	render_line(t_img *img, t_line line, int color)
{
	int	i;
	int	j;
	int	func;

	i = line.s_y;
	while (i <= line.g_y)
	{
		j = line.s_x;
		while (j <= line.g_x)
		{
			func = (i - line.s_y) * (line.g_x - line.s_x) - (j - line.s_x) * (line.g_y - line.s_y);
			if (abs(func) < 100) //オーバーフローケアするように要修正。
				img_pix_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

void	render_square(t_img *img, t_square point, int color)
{
	int	i;
	int	j;
	
	render_line(img, (t_line){point.s_x, point.s_y, point.s_x, point.g_y}, color);
	render_line(img, (t_line){point.s_x, point.s_y, point.g_x, point.s_y}, color);
	render_line(img, (t_line){point.s_x, point.g_y, point.g_x, point.g_y}, color);
	render_line(img, (t_line){point.g_x, point.s_y, point.g_x, point.g_y}, color);
}

int	render(t_data *data, t_map *list)
{
	if (!data->win_ptr)
		return (1);
	render_background(&data->img, WHITE_PIXEL);
	render_square(&data->img, (t_square){WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10, WINDOW_WIDTH * 9 / 10, WINDOW_HEIGHT * 9 / 10}, BLACK_PIXEL);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	//4th and 5th arguments indicate the starting position (coordinates).
	//Perhaps, you can use this as a zooming or moving functions.
	return (0);
}

int	show_screen(t_map *map)
{
	t_data	data;

	data.map = map;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "window");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), MLX_ERROR);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	return (free(data.mlx_ptr), 0);
}

int	main(int argc, char *argv[])
{
	int			fd;
	char		*txt;
	t_map	*list;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	txt = get_txt(fd);
	close(fd);
	if (!txt)
		return (1);
	list = get_map(txt);
	free(txt);
	if (!list)
		return (1);
	if (show_screen(list))
		return (free_int_list(list, list->y), 1);
	return (free_int_list(list, list->y), 0);
}
