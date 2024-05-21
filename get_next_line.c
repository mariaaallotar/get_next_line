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

char	*free_everything(char *read_buf, char *line, char *rest)
{
	if (read_buf != NULL)
		free(read_buf);
    if (line != NULL)
		free(line);
    if (rest != NULL)
		free(rest);
    read_buf = NULL;
    line = NULL;
    rest = NULL;
	return (NULL);
}

char	*join_rest_read(char *read_buf, char *line, char **rest)
{
	char		*new_rest;
	size_t		rest_len;
	size_t		read_len;

	rest_len = ft_strlen(*rest);
	read_len = ft_strlen(read_buf);
	new_rest = (char *) calloc((rest_len + read_len + 1), sizeof (char)); //change calloc to something else
	if (new_rest == NULL)
		return (free_everything(read_buf, line, *rest));
	ft_strlcat(new_rest, *rest, (rest_len + read_len + 1));
	ft_strlcat(new_rest, read_buf, (rest_len + read_len + 1));
	free(*rest);
	*rest = NULL; //maybe unecessary
	return (new_rest);
}

char	*create_line_and_rest(char *read_buf, char **rest)
{
	char	*new_rest;
	char	*line;
	char	*orig_line;

	//possibly too much space allocated for line
	line = (char *) calloc((ft_strlen(*rest) + 1), sizeof(char)); //change calloc to something else
	if (line == NULL)
		return (free_everything(read_buf, line, *rest));
	orig_line = line;
	while (**rest != '\0')
	{
		*line = **rest;
		(*rest)++;
		if (*line == '\n')
			break;
		line++;
	}
	new_rest = (char *) calloc((ft_strlen(*rest) + 1), sizeof(char)); //change calloc to something else
	if (new_rest == NULL)
		return (free_everything(read_buf, line, *rest));
	new_rest[ft_strlen(*rest)] = '\0';
	ft_strlcat(new_rest, *rest, ft_strlen(*rest) + 1);
	if (*rest != NULL)
		free(*rest);
	*rest = new_rest;
	return (orig_line);
}

char	*read_next_line(int fd, char **rest)
{
	char	*read_buf;
	ssize_t	bytes_read;
	char	*line;

	read_buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (read_buf == NULL)
		return (free_everything(read_buf, NULL, *rest));
	while (ft_strchr(*rest, '\n') == NULL)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_everything(read_buf, NULL, *rest));
		if (bytes_read == 0)
		{
			line = create_line_and_rest(read_buf, rest);
			return (line);
		}
		read_buf[bytes_read] = '\0';
		*rest = join_rest_read(read_buf, NULL, rest);
		if (*rest == NULL)
			return (free_everything(read_buf, NULL, *rest)); //probably uncessary at this point
	}
	line = create_line_and_rest(read_buf, rest);
	if (line == NULL)
		return (free_everything(read_buf, line, *rest)); //probably uncessary at this point
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
