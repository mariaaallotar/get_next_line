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

char	*join_rest_read(char *rest, char *read_buf)
{
	char		*new_rest;
	size_t		rest_len;
	size_t		read_len;

	if (!rest || !read_buf)
		return (NULL);
	rest_len = ft_strlen(rest);
	read_len = ft_strlen(read_buf);
	new_rest = (char *) malloc((rest_len + read_len + 1) * sizeof (char));
	if (new_rest == NULL)
		return (NULL);
	ft_strlcat(new_rest, rest, (rest_len + read_len + 1));
	ft_strlcat(new_rest, read_buf, (rest_len + read_len + 1));
	free(rest);
	return (new_rest);
}

char	*read_to_rest(int fd, char *rest)
{
	char	*read_buf;
	int		read_bytes;

	//allocate read buffer
	read_buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	//check that allocation worked
	if (!read_buf)
		return (NULL);
	//while rest does not contain newline and bytes read is not 0
	read_bytes = 1;
	if (!rest)
	{
		rest = (char *) malloc(1 * sizeof(char));
		rest[0] = '\0';
	}
	while (!ft_strchr(rest, '\n') && read_bytes != 0)
	{
		//read into buffer and save bytes read
		read_bytes = read(fd, read_buf, BUFFER_SIZE);
		//check that reading was successfull
		if (read_bytes == -1)
		{
			//if not free the read buffer
			free(read_buf);
			return (NULL);
		}
		//nullterminate the readbuffer
		read_buf[BUFFER_SIZE] = '\0';
		//create the rest string by combining the rest and read buffer and freeing the old rest
		rest = join_rest_read(rest, read_buf);
	}
	//now we have a new line in rest, so lets free the read buffer
	free(read_buf);
	return (rest);
}

char	*get_line_from_rest(char *rest)
{
	int		i;
	char	*line;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
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

char	*get_new_rest(char *rest)
{
	char	*new_rest;
	int		i;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	new_rest = (char *)malloc((ft_strlen(rest) - i + 1) * sizeof(char));
	if (!new_rest)
		return (NULL);
	ft_strlcat(new_rest, rest + i + 1, (ft_strlen(rest) - i + 1));
	free(rest);
	return (new_rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	//check that fd is bigger than or equal to 0 and BUFFER_SIZE is bigger than 0
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//create rest (rest is at this point everything read containing newline or end) with read_to_rest()
	rest = read_to_rest(fd, rest);
	//check that the creation of rest went well
		//if not: return NULL
	if (!rest)
		return (NULL);
	//get the next line into its own variable, nothing more
	line = get_line_from_rest(rest);
	//remove the next line from rest and create a new rest (the acctual rest), free everything else than the new rest
	rest = get_new_rest(rest);
	//return the line
	return (line);
}
