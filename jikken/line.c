#include "jikken.h"

static void	draw_horizontal_vertical(t_img *img, t_line *line, int color);
static void	draw_bigger_than_one(t_img *img, t_line *line, int color);
static void	draw_less_than_one(t_img *img, t_line *line, int color);

void	draw_line(t_img *img, t_point a, t_point b, int color)
{
	t_line	line;
	t_point	d;

	d.x = ft_abs(a.x - b.x);
	d.y = ft_abs(a.y - b.y);
	line.d = &d;
	line.a = &a;
	line.b = &b;
	if (d.y == 0 || d.x == 0)
		draw_horizontal_vertical(img, &line, color);
	else if (d.y > d.x)
		draw_bigger_than_one(img, &line, color);
	else
		draw_less_than_one(img, &line, color);
}

static void	draw_horizontal_vertical(t_img *img, t_line *line, int color)
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

static void	draw_bigger_than_one(t_img *img, t_line *line, int color)
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

static void	draw_less_than_one(t_img *img, t_line *line, int color)
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
