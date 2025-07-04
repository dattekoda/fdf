/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 06:18:52 by khanadat          #+#    #+#             */
/*   Updated: 2025/07/04 12:14:10 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test/test.h"

int	atoi_base(const char *nptr, const char *base)
{
	int		num;
	int		sign;
	size_t	base_len;
	char	*base_ptr;

	num = 0;
	sign = 1;
	base_len = ft_strlen(base);
	while (*nptr == ' ' || ('\t' <= *nptr && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		sign = -1 + 2 * (*(nptr++) == '+');
	while (*nptr)
	{
		base_ptr = ft_strchr(base, ft_tolower(*nptr++));
		if (!base_ptr)
			break;
		num = num * base_len + (base_ptr - &base[0]);
	}
	return (sign * num);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(int argc, char* argv[])
// {
// 	if (argc != 2) return 0;
// 	printf("original: |%s|\n", argv[1]);
// 	printf("atoi:     |%d|\n", atoi(argv[1]));
// 	printf("ft_atoi:  |%d|\n", atoi_base(argv[1], "0123456789abcdef"));
// 	return 0;
// }