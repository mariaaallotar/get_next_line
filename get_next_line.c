/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:25:38 by maheleni          #+#    #+#             */
/*   Updated: 2024/05/13 12:25:39 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remain = "\0";
	char		*read_buf;
	char		*big_buf;
	int			i;
	char		*line;

	read_buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (1)
	{
		read(fd, (void *) read_buf, BUFFER_SIZE);
		read_buf[BUFFER_SIZE] = '\0';
		big_buf = ft_strjoin(remain, read_buf);
		i = ft_findchr(big_buf, '\n');
		if (i)
		{
			line = ft_substr(big_buf, 0, i + 1);
			if (line == NULL)
			{
				free(read_buf);
				free(big_buf);
				return (NULL);
			}
			remain = ft_substr(big_buf, i + 1, ft_strlen(big_buf) - ft_strlen (line));
			free(read_buf);
			free(big_buf);
			return(line);
		}
		i = -1;
		i = ft_findchr(big_buf, '\0');
		if (i != -1 && i != ft_strlen(big_buf))
		{
			line = ft_substr(big_buf, 0, i + 1);
			if (line == NULL)
			{
				free(read_buf);
				free(big_buf);
				return (NULL);
			}
			free(read_buf);
			free(big_buf);
			return (line);
		}
	}
	return (NULL);
}
