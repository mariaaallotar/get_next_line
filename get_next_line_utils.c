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

#include "get_next_line.h"

/**
* Appends (concatenate) string src to the end of dst
*	It will append at most dstsize - strlen(dst) - 1 characters.  
*	It will then NUL-terminate, unless dstsize is 0 or the original dst string
*	was longer than dstsize
* If the src and dst strings overlap, the behavior is undefined.
* Parameters:
*	*dst - the destination to append to
*	*src - the source to copy from
*	dstsize - the size of dst memory
* Returns:
*	The size of the string it tried to create, in practice the initial length
*		of dst plus the length of src
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize > dst_len && dstsize > 0)
	{
		i = 0;
		while (i < dstsize - dst_len - 1 && i < src_len)
		{
			dst[i + dst_len] = src[i];
			i++;
		}
		dst[i + dst_len] = '\0';
	}
	if (dst_len >= dstsize)
		dst_len = dstsize;
	return (dst_len + src_len);
}

/**
* Locates the first occurrence of c (converted to a char) in the string 
*	pointed to by s.
* The terminating null character is considered to be part of the 
*	string; therefore if c is `\0', the functions locate the terminating `\0'.
* Parameters:
*	*s - pointer to the string to find character c from
*	c - int representation of the character to find
* Returns:
*	Pointer to the first occurance of the character found.
*	NULL if c is not found anywhere in the string
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if ((char) c == '\0')
		return ((char *) s);
	return (NULL);
}

/**
* Computes the length of the string s
* Parameters: 
	*s - string to get length of
* Returns: 
	The length of the string (amount of character before '\0' character)
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}