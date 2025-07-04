#include "../test/test.h"

char	*txt = "1,0xFFFFFF 0,0xFFFFFF\n1,0x00FF00 1,0x00FF00";

uint32_t	get_color(const char *elem, const char *base)
{
	uint32_t	num;
	size_t		base_len;
	char		*base_ptr;

	num = 0;
	base_len = ft_strlen(base);
	while (*elem && *elem != ' ' && *elem != '\n')
	{
		base_ptr = ft_strchr(base, ft_tolower(*elem++));
		if (!base_ptr)
			break ;
		num = num * base_len + (base_ptr - &base[0]);
	}
	return (num);
}

int	have_color(char **elem)
{
	char	*confirm;
	char	*space_ptr;
	char	*new_line_ptr;

	confirm = ft_strchr(*elem, ',');
	space_ptr =ft_strchr(*elem, ' ');
	new_line_ptr =ft_strchr(*elem, '\n');
	if ((space_ptr && confirm >= space_ptr) ||
		(new_line_ptr && confirm >= new_line_ptr) ||
		confirm >= ft_strchr(*elem, '\0'))
		return (0);
	*elem = confirm + 3;
	return (1);
}

char	*get_elem(char *txt, int x, int y)
{
	char	*elem = txt;

	elem = txt;
	while (y--)
		elem = ft_strchr(elem, '\n') + 1;
	while (*elem == ' ')
		elem++;
	while (x--)
	{
		elem = ft_strchr(elem, ' ');
		while (*elem == ' ')
			elem++;
	}
	return (elem);
}

int	main(void)
{
	char	*str = "7,0xff 5,0x00 3,0xff\n    4,0xff   2,0xff -9,0x00";
	char	*elem;

	elem = get_elem(str, 0,1);
	printf("%s\n", elem);
	printf("%d\n", ft_atoi(elem));
	if (have_color(&elem))
		printf("%d\n", get_color(elem, "0123456789abcdef"));
	return (SUCCESS);
}

// t_coords	*set_coords(t_coords elems)
// {
// 	t_coords *coords;

// 	coords = malloc(sizeof(t_coords));
// 	if (!coords)
// 	return (NULL);
// 	coords->left = NULL;
// 	coords->up = NULL;
// 	coords->x = elems.x;
// 	coords->y = elems.y;
// 	coords->z = elems.z;
// 	return (coords);
// }

//line = splited line char like ""0,0xFFFFFF", "1,0xFFFFFF""
// t_coords	*add_coordinates(t_input *input, t_coords *left, t_coords *upper)
// {
// 	t_coords	*coords;
// 	static int	sta_x = 0;
// 	static int	sta_y = 0;

// 	sta_x = (sta_x + 1) % input->num_c;
// 	if (!left)
// 		sta_y++;
// 	coords = set_coords((t_coords){sta_x, sta_y, ft_atoi(get_elem(input->txt, sta_x, sta_y))});
// 	if (!coords)
// 		return (NULL);

// 	return (NULL);
// }