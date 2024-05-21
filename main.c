
#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main()
{
	int	i = 10;
	int fd = open("empty.txt", O_RDONLY);
	while (i > 0)
	{
		printf("%s\n", get_next_line(fd));
		printf("one line was returned\n");
		i--;
	}
	close(fd);
}