/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:15:22 by maheleni          #+#    #+#             */
/*   Updated: 2024/05/20 10:15:24 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_everything(char *read_buf, char *line, char **rest_ptr)
{
	if (read_buf != NULL)
		free(read_buf);
    if (line != NULL)
		free(line);
    if (*rest_ptr != NULL)
		free(*rest_ptr);
    read_buf = NULL;
    line = NULL;
    *rest_ptr = NULL;
	return (NULL);
}

char	*join_rest_read(char *read_buf, char *line, char **rest_ptr)
{
	char		*new_rest;
	size_t		rest_len;
	size_t		read_len;

	rest_len = ft_strlen(*rest_ptr);
	read_len = ft_strlen(read_buf);
	new_rest = (char *) calloc((rest_len + read_len + 1), sizeof (char)); //change calloc to something else
	if (new_rest == NULL)
		return (free_everything(read_buf, line, rest_ptr));
	ft_strlcat(new_rest, *rest_ptr, (rest_len + read_len + 1));
	ft_strlcat(new_rest, read_buf, (rest_len + read_len + 1));
	free(*rest_ptr);
	*rest_ptr = NULL; //maybe unecessary
	return (new_rest);
}

char	*create_line_and_rest(char *read_buf, char **rest_ptr)
{
	char	*new_rest;
	char	*line;
	char	*orig_line;
	char	*orig_rest;

	//possibly too much space allocated for line
	line = (char *) calloc((ft_strlen(*rest_ptr) + 1), sizeof(char)); //change calloc to something else
	if (line == NULL)
		return (free_everything(read_buf, line, rest_ptr));
	orig_line = line;
	orig_rest = *rest_ptr;
	while (**rest_ptr != '\0')
	{
		*line = **rest_ptr;
		(*rest_ptr)++;
		if (*line == '\n')
			break;
		line++;
	}
	*line = '\0';
	new_rest = (char *) calloc((ft_strlen(*rest_ptr) + 1), sizeof(char)); //change calloc to something else
	if (new_rest == NULL)
		return (free_everything(read_buf, line, rest_ptr));
	new_rest[ft_strlen(*rest_ptr)] = '\0';
	ft_strlcat(new_rest, *rest_ptr, ft_strlen(*rest_ptr) + 1);
	if (*rest_ptr != NULL)
	free(orig_rest);
	orig_rest = NULL;
	*rest_ptr = new_rest;
	return (orig_line);
}

char	*read_next_line(int fd, char **rest_ptr)
{
	char	*read_buf;
	ssize_t	bytes_read;
	char	*line;

	read_buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (read_buf == NULL)
		return (free_everything(read_buf, NULL, rest_ptr));
	while (ft_strchr(*rest_ptr, '\n') == NULL)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_everything(read_buf, NULL, rest_ptr));
		if (bytes_read == 0)
		{
			if (**rest_ptr == '\0')
				return (free_everything(read_buf, NULL, rest_ptr));
			line = create_line_and_rest(read_buf, rest_ptr);
			free_everything(read_buf, NULL, rest_ptr);
			return (line);
		}
		read_buf[bytes_read] = '\0';
		*rest_ptr = join_rest_read(read_buf, NULL, rest_ptr);
		if (*rest_ptr == NULL)
			return (free_everything(read_buf, NULL, rest_ptr)); //probably uncessary at this point
	}
	line = create_line_and_rest(read_buf, rest_ptr);
	if (line == NULL)
		return (free_everything(read_buf, line, rest_ptr)); //probably uncessary at this point
	free(read_buf);
	read_buf = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
	{
		rest = (char *) calloc(1, sizeof(char)); //change calloc to something else
		if (rest == NULL)
			return (NULL);
		rest[0] = '\0';
	}
	if (ft_strchr(rest, '\n'))
	{
		line = create_line_and_rest(NULL, &rest);
		if (line == NULL)
			return (NULL);
		return (line);
	}
	line = read_next_line(fd, &rest);
	return (line);
}
