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

int	ft_findchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == (char) c)
			return (i);
		s++;
		i++;
	}
	if ((char) c == '\0')
		return (i);
	return (i);
}

/**
* Allocates and returns a substring from the string 's'
* Parameters:
*	*s - string to create substring from
*	start - start index of the substring in the string 's'
*	len - maximum length of the substring (NOT including '\0')
* Returns:
*	The substring
*	NULL if allocation fails or 's' is NULL
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	sub = (char *) malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
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

/**
* Copies up to (dstsize - 1) characters from the string src to dst,
* 	NUL-terminating the result if dstsize is not 0.
* If the src and dst strings overlap, the behavior is undefined.
* Parameters:
*	*dst - the destination to copy to
*	*src - the source to copy from
*	dstsize - the size of dst memory
* Returns:
*	The size of the string it tried to copy, in practice the size of src
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		i = 0;
		while (i < src_len && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

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
* Allocates sufficient memory for a copy of the string s1, does the copy,
*	and returns a pointer to it.  The pointer may subsequently be used as an
*	argument to the function free
* Parametes:
*	*s1 - string to duplicate
* Returns:
*	Pointer to the duplicated string
*/
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s1);
	dup = (char *) malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s1, len + 1);
	return (dup);
}

/**
* Copies n bytes from memory area src to memory area dst.
* If dst and src overlap, behavior is undefined.
* Parameters: 
	*dst - the destination to copy bytes to
	*src - the source to copy from
	n - amount of bytes to cpy
* Returns: 
	The destination
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*orig_dst;

	orig_dst = dst;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (n > 0)
	{
		*(char *)dst = *(char *)src;
		dst++;
		src++;
		n--;
	}
	return (orig_dst);
}
