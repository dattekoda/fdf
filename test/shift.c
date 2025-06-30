#include <stdio.h>
#include <stdint.h>
int	main(void)
{
	uint32_t	color = 0b001111011;
	uint32_t	i = 2;

	printf("%u\n", color);
	printf("%u\n", 0b00111101100);
	printf("%u\n", color << i);
}