/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haras <haras@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:58:26 by haras             #+#    #+#             */
/*   Updated: 2025/08/02 20:30:04 by haras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_store(int fd, char *static_buff)
{
	char	*buf;
	char	*temp;
	int		bytes_read;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(static_buff, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			free(static_buff);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		if (!static_buff)
			temp = ft_strjoin("", buf);
		else
			temp = ft_strjoin(static_buff, buf);
		free(static_buff);
		static_buff = temp;
	}
	free(buf);
	return (static_buff);
}


char	*get_next_line(int fd)
{
	static char	*static_buff;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_buff = read_and_store(fd, static_buff);
	if (!static_buff)
		return (NULL);
	return (result);
}
