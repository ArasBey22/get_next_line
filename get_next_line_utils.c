/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haras <haras@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:58:32 by haras             #+#    #+#             */
/*   Updated: 2025/08/06 14:13:42 by haras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

char	*ft_strdup(const char *s)
{
	size_t	length;
	size_t	index;
	char	*location_pointer;

	length = ft_strlen(s);
	location_pointer = (char *)malloc(sizeof(char) * (length + 1));
	if (!location_pointer)
		return (NULL);
	index = 0;
	while (index < length)
	{
		location_pointer[index] = s[index];
		index++;
	}
	location_pointer[index] = '\0';
	return (location_pointer);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	source_len;
	size_t	index;
	char	*target;

	if (!s)
		return (NULL);
	source_len = ft_strlen(s);
	if (source_len <= start)
		return (ft_strdup(""));
	if (len > source_len - start)
		len = source_len - start;
	target = (char *)malloc(sizeof(char) * (len + 1));
	if (!target)
		return (NULL);
	index = 0;
	while (s[index + start] && index < len)
	{
		target[index] = s[start + index];
		index++;
	}
	target[index] = '\0';
	return (target);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		index;
	int		s1_len;
	int		s2_len;
	char	*new_string;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_string = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_string)
		return (NULL);
	index = 0;
	while (*s1)
		new_string[index++] = *s1++;
	while (*s2)
		new_string[index++] = *s2++;
	new_string[index] = '\0';
	return (new_string);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*pointer;

	if (!s)
		return (NULL);
	pointer = (char *)s;
	i = 0;
	while (pointer[i] != '\0')
	{
		if (pointer[i] == (unsigned char)c)
			return (pointer + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (pointer + i);
	return (NULL);
}
