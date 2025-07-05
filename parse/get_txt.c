#include "../test/test.h"

char	*get_txt(int fd)
{
	char	*buf;
	char	*txt;
	char	*tmp;
	size_t	buf_size;
	ssize_t	n;

	txt = ft_strdup("");
	buf_size = 4096; //cpuが一回に読み込める最大量 getconf PAGE_SIZE
	while (txt)
	{
		buf = malloc(buf_size + 1);
		if (!buf)
			return (free(txt), NULL);
		n = read(fd, buf, buf_size);
		if (n < 0)
			return (free(txt), free(buf), NULL);
		else if (n == 0)
			return (free(buf), txt);
		buf[n] = '\0';
		tmp = txt;
		txt = ft_strjoin(tmp, buf);
		buf_size *= (free(tmp), free(buf), 2);
	}
	return (txt);
}

int	main(int argc, char *argv[])
{
	int	fd;
	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	char	*txt = get_txt(fd);
	printf("%s\n", txt);
	free(txt);
	close(fd);
	return (0);
}
