/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:14:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/06 02:55:47 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static double	get_percentage(int start, int goal, int current);
static int		get_grad(int start, int goal, double p);

int	calc_color(t_line *line, t_point current, bool big)
{
	int		red;
	int		green;
	int		blue;
	double	p;

	if (line->s->color == line->g->color)
		return (line->s->color);
	else if (big)
		p = get_percentage(line->s->y, line->g->y, current.y);
	else
		p = get_percentage(line->s->x, line->g->x, current.x);
	red = get_grad((line->s->color >> 16) & 0xFF,
			(line->g->color >> 16) & 0xFF, p);
	green = get_grad((line->s->color >> 8) & 0xFF,
			(line->g->color >> 8) & 0xFF, p);
	blue = get_grad(line->s->color & 0xFF,
			line->g->color & 0xFF, p);
	return ((red << 16) | (green << 8) | blue);
}

static double	get_percentage(int start, int goal, int current)
{
	double	child;
	double	mom;

	child = current - start;
	mom = goal - start;
	if (mom == 0)
		return (1);
	return (child / mom);
}

static int	get_grad(int start, int goal, double p)
{
	return ((int)((1 - p) * start + p * goal));
}

// int main(void)
// {
// 	t_point a;
// 	t_point b;
// 	t_point d;
// 	t_point curr;
// 	t_line	line;

// 	a.x = 0;
// 	a.y = 0;
// 	a.color = 0xffffff;
// 	b.x = 20;
// 	b.y = 255;
// 	b.color = 0x000000;
// 	d.x = ft_abs(a.x - b.x);
// 	d.y = ft_abs(a.y - b.y);
// 	line.d = &d;
// 	line.s = &b;
// 	line.g = &a;
// 	curr.x = (b.x - a.x) / 2 + a.x;
// 	curr.y = (b.y - a.y) / 2 + a.y;
// 	if (a.x < b.x)
// 	{
// 		line.s = &a;
// 		line.g = &b;
// 	}
// 	printf("%d\n", a.color);
// 	printf("%d\n", calc_color(&line, curr, (d.y > d.x)));
// 	return (0);
// }