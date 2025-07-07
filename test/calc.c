#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

int	main(void)
{
	int	x = -1;
	int	y = -1;
	int	z = -1;
	double	angle = M_PI * 2 / 5;
	int	zoom = 100;
	int	offset_x = 300;
	int	offset_y = 300;

	while (++z < 2)
	{
		x = -1;
		while (++x < 2)
		{
			y = -1;
			while (++y < 2)
			{
				double	sx = (x - y) * cos(angle) * zoom + offset_x;
				double	sy = (x + y) * sin(angle) * zoom + offset_y + z * zoom;
				printf("%d, %d, ", (int)sx, (int)sy);
			}
		}
		printf("\n");
	}
	return (0);
}