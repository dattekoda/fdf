#include "jikken.h"

void	img_put_pix(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || WINDOW_WIDTH < x || y < 0 || WINDOW_HEIGHT < y)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	if (img->endian) // big endian
	{
		pixel[0] = (color >> 24) & 0xFF; //A
		pixel[1] = (color >> 16) & 0xFF; //R
		pixel[2] = (color >> 8) & 0xFF; //G
		pixel[3] = color & 0xFF; //B
		return ;
	}
	// little endian
	pixel[0] = color & 0xFF; //B
	pixel[1] = (color >> 8) & 0xFF; //G
	pixel[2] = (color >> 16) & 0xFF; //R
	pixel[3] = (color >> 24) & 0xFF; //A
}
