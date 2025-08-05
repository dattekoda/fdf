#include "jikken.h"

void	img_put_pix(t_img *img, int x, int y, int color)
{
	int		i;

	if (0 <= x && x < WINDOW_WIDTH && 0 <= y && y < WINDOW_HEIGHT)
	{
		i = (x * img->bpp / 8) + (y * img->line_len);
		img->addr[i] = color;
		img->addr[++i] = color >> 8;
		img->addr[++i] = color >> 16;
	}
}
