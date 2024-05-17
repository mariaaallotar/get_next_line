/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:33:46 by maheleni          #+#    #+#             */
/*   Updated: 2024/05/17 10:33:48 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_rest_read(char *rest, char *read_buf)
{
	char		*new_rest;
	size_t		rest_len;
	size_t		read_len;

	if (rest == NULL)
	{
		rest = (char *) malloc(1 * sizeof(char));
		if (rest == NULL)
			return (NULL);
		rest[0] = '\0';
	}
	rest_len = ft_strlen(rest);
	read_len = ft_strlen(read_buf);
	new_rest = (char *) calloc((rest_len + read_len + 1), sizeof (char)); //chage calloc to something else
	if (new_rest == NULL)
		return (NULL);
	ft_strlcat(new_rest, rest, (rest_len + read_len + 1));
	ft_strlcat(new_rest, read_buf, (rest_len + read_len + 1));
	free(rest);
	return (new_rest);
}

char	*create_line(char *rest)
{
	int		i;
	char	*line;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
	{
		line[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
	{
		line[i] = rest[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*free_and_return(char *read_buf, char *rest, ssize_t situation)
{
	char	*line;

	if (read_buf != NULL)
		free(read_buf);
	if (situation == -1) //read_buf, new_rest or line allocation failed or read had error, rest might be allocated RETURN NULL
	{
		if (rest != NULL)
			free(rest);
		return (NULL);
	}
	else if (situation == 0) //nothing read, rest might be allocated, return line of all rest or NULL if rest is not allocated
	{
		if (rest != NULL)
		{
			line = create_line(rest);
			if (line == NULL)
				return(free_and_return(read_buf, rest, -1));
			free(rest);
			return (line);
		}
		return (NULL);
	}
	if (rest == NULL)
	{
		rest = (char *) malloc (1 * sizeof(char));
		if (rest == NULL)
			return (NULL);
		rest[0] = '\0';
	}
	return(create_line(rest));
}

char	*read_next_line(int fd)
{
	ssize_t	bytes_read;
	char	*read_buf;
	static char	*rest;

	read_buf = (char *) malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (read_buf == NULL)
		return (free_and_return(read_buf, rest, -1));
	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return(free_and_return(read_buf, rest, -1));
		if (bytes_read > 0)
			read_buf[bytes_read] = '\0';
		rest = join_rest_read(rest, read_buf);
		if (rest == NULL)
			return (free_and_return(read_buf, rest, -1));
		if (ft_strchr(rest, '\n') != NULL) //we have read a full line
			break;
	}
	//at this point we have a buffer with a new line or we are at end of file
	//we are sure that rest is allocated
	//we want to return a line and free everything not necessary anymore
	return (free_and_return(read_buf, rest, bytes_read));
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (read_next_line(fd));
}
