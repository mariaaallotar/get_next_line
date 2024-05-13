/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:12:37 by maheleni          #+#    #+#             */
/*   Updated: 2024/05/13 16:12:39 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* Allocates and returns a new string, which is the result of the concatenation
*	of 's1' and 's2'
* Parameters:
*	*s1 - the prefix string
*	*s2 - the suffix string
* Returns:
*	The string
*	NULL if allocation failed
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *) malloc((s1_len + s2_len + 1) * sizeof (char));
	if (join == NULL)
		return (NULL);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcat(join, s2, (s1_len + s2_len + 1));
	return (join);
}

/**
* Locates the last occurrence of c (converted to a char) in the string 
*	pointed to by s.
* The terminating null character is considered to be part of the 
*	string; therefore if c is `\0', the functions locate the terminating `\0'.
* Parameters:
*	*s - pointer to the string to find character c from
*	c - int representation of the character to find
* Returns:
*	Pointer to the last occurance of the character found.
*	NULL if c is not found anywhere in the string
*/
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	if ((char) c == '\0')
		return ((char *) s);
	while (i >= 0)
	{
		if (*s == (char) c)
			return ((char *) s);
		s--;
		i--;
	}
	return (NULL);
}
