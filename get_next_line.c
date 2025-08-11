/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haras <haras@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:58:26 by haras             #+#    #+#             */
/*   Updated: 2025/08/11 15:51:44 by haras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*insert_front(char *static_buffer, char *read_text)
{
	char	*new_static_buffer;

	if (!static_buffer)
		new_static_buffer = ft_strjoin("", read_text);
	else
		new_static_buffer = ft_strjoin(static_buffer, read_text);
	if (!new_static_buffer)
	{
		free(read_text);
		free(static_buffer);
		return (NULL);
	}
	free(static_buffer);
	return (new_static_buffer);
}

static char	*read_and_store(int fd, char *static_buffer)
{
	char	*read_text;
	ssize_t		bytes_read;

	read_text = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_text)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(static_buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_text, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_text);
			free(static_buffer);
			return (NULL);
		}
		read_text[bytes_read] = '\0';
		static_buffer = insert_front(static_buffer, read_text);
		if (!static_buffer)
			return (NULL);
	}
	free(read_text);
	return (static_buffer);
}

static char	*get_line(char *static_buffer)
{
	int		index;
	char	*line;

	if (!static_buffer || static_buffer[0] == '\0')
		return (NULL);
	index = 0;
	while (static_buffer[index] && static_buffer[index] != '\n')
		index++;
	if (static_buffer[index] == '\n')
		index++;
	line = ft_substr(static_buffer, 0, index);
	return (line);
}

static char	*update_and_free(char *static_buffer)
{
	char	*new_static_buffer;
	int		index;
	int		len;

	index = 0;
	while (static_buffer[index] && static_buffer[index] != '\n')
		index++;
	if (static_buffer[index] == '\0')
		return (free(static_buffer), NULL);
	len = ft_strlen(static_buffer) - index - 1;
	new_static_buffer = ft_substr(static_buffer, index + 1, len);
	if (!new_static_buffer)
		return (NULL);
	free(static_buffer);
	return (new_static_buffer);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_buffer = read_and_store(fd, static_buffer);
	if (!static_buffer)
		return (NULL);
	result = get_line(static_buffer);
	static_buffer = update_and_free(static_buffer);
	return (result);
}
