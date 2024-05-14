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

//fix headerfile and utils
int	ft_findchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);

char	*get_next_line(int fd)
{
	char		*read_buf;
	static char	*rest = "\0";
	char		*line;
	int			line_end_i;
	char		*temp;
	ssize_t		bytes_read;

	while (1)
	{
		read_buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char)); //allocate memery to read into + to null terminate
		if (read_buf == NULL)
			return (NULL);
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			line = ft_strdup(rest);
			//free(read_buf);
			//free(rest);
			return (line);
		} else if (bytes_read == -1)
		{
			//free(read_buf);
			//free(rest);
			return (NULL);
		}
		read_buf[BUFFER_SIZE] = '\0';
		temp = ft_strjoin(rest, read_buf);
		//free(rest);
		//free(read_buf);
		if (temp == NULL)
			return (NULL);
		line_end_i = ft_findchr(temp, '\n');
		if (line_end_i != -1)
		{
			line = ft_substr(temp, 0, line_end_i + 1);
			if (line == NULL)
			{
				//free(temp);
				return(NULL);
			}
			rest = ft_strdup(temp + ft_strlen(line));
			return(line);
		}
		line_end_i = ft_findchr(temp, '\0');
		if (line_end_i)
		{
			line = ft_strdup(temp);
			//free(temp);
			return (line);
		}
	}
	return(NULL);
}
