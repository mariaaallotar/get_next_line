
#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main()
{
	int	i = 3;
	int fd = open("giant_line.txt", O_RDONLY);
	while (i > 0)
	{
		char *line = get_next_line(fd);
		printf("%s", line);
		i--;
		if (line != NULL)
			free(line);
	}
	close(fd);
}