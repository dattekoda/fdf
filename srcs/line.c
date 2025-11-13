/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:38:37 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/09 14:50:03 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	draw_bigger_than_one(t_img *img, t_line *line);
static void	draw_less_than_one(t_img *img, t_line *line);
static void	set_draw_line(int *discriminant, int *append,
				t_line *line, bool big);

void	draw_line(t_img *img, t_point a, t_point b)
{
	t_line	line;
	t_point	d;

	d.x = ft_abs(a.x - b.x);
	d.y = ft_abs(a.y - b.y);
	line.d = &d;
	line.s = &b;
	line.g = &a;
	if (a.x < b.x)
	{
		line.s = &a;
		line.g = &b;
	}
	if (d.x == 0 && d.y == 0)
		img_put_pix(img, a.x, a.y, a.color);
	else if (d.y > d.x)
		draw_bigger_than_one(img, &line);
	else
		draw_less_than_one(img, &line);
}

static void	draw_bigger_than_one(t_img *img, t_line *line)
{
	int		discriminant;
	int		append;
	t_point	curr;

	set_draw_line(&discriminant, &append, line, 1);
	curr = *(line->s);
	curr.y--;
	while (++(curr.y) <= line->g->y)
	{
		img_put_pix(img, curr.x, curr.y,
			calc_color(line, curr, 1));
		if (discriminant < 0)
		{
			discriminant += 2 * line->d->y - 2 * line->d->x;
			curr.x += append;
		}
		else
			discriminant += -2 * line->d->x;
	}
}

static void	draw_less_than_one(t_img *img, t_line *line)
{
	int		discriminant;
	int		append;
	t_point	curr;

	set_draw_line(&discriminant, &append, line, 0);
	curr = *(line->s);
	curr.x--;
	while (++(curr.x) <= line->g->x)
	{
		img_put_pix(img, curr.x, curr.y,
			calc_color(line, curr, 0));
		if (discriminant > 0)
		{
			discriminant += -2 * line->d->x + 2 * line->d->y;
			curr.y += append;
		}
		else
			discriminant += 2 * line->d->y;
	}
}

static void	set_draw_line(int *discriminant, int *append,
		t_line *line, bool big)
{
	t_point	*tmp;

	*append = 1;
	if (big)
	{
		if (line->g->y < line->s->y)
		{
			tmp = line->s;
			line->s = line->g;
			line->g = tmp;
		}
		if (line->g->x < line->s->x)
			*append = -1;
		*discriminant = -2 * line->d->x + line->d->y;
		return ;
	}
	if (line->g->y < line->s->y)
		*append = -1;
	*discriminant = 2 * line->d->y - line->d->x;
}
