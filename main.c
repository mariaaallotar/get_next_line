
#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main()
{
	int	i = 10;
	int fd = open("file.txt", O_RDONLY);
	while (i > 0)
	{
		printf("%s", get_next_line(fd));
		i--;
	}
	close(fd);
}