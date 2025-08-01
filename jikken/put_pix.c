#include "jikken.h"

// void	img_put_pix(t_img *img, int x, int y, int color)
// {
// 	char	*pixel;

// 	pixel = NULL;
// 	if (0 <= x && x < WINDOW_WIDTH && 0 <= y && y < WINDOW_HEIGHT)
// 		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
// 	if (img->endian) // big endian
// 	{
// 		pixel[0] = (color >> 24) & 0xFF; //A
// 		pixel[1] = (color >> 16) & 0xFF; //R
// 		pixel[2] = (color >> 8) & 0xFF; //G
// 		pixel[3] = color & 0xFF; //B
// 		return ;
// 	}
// 	// little endian
// 	pixel[0] = color & 0xFF; //B
// 	pixel[1] = (color >> 8) & 0xFF; //G
// 	pixel[2] = (color >> 16) & 0xFF; //R
// 	pixel[3] = 0xFF;
// }

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
