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

char	*get_next_line(int fd)
{
	static char	*remain = "\0";
	void		*read_buf;
	char		*big_buf;
	int			i;
	char		*line;

	while (true)
	{
		read(fd, read_buf, BUFFER_SIZE);
		big_buf = ft_strjoin(remain, read_buf);
		i = ft_strchr(big_buf, "\n");
		if (i)
		{
			line = ft_substr(big_buf, 0, i + 1);
			if (line == NULL)
			{
				free_everything();
				return (NULL)
			}
			free(read_buf);
			
		}
	}
}
