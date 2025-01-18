/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:18:12 by albernar          #+#    #+#             */
/*   Updated: 2024/11/16 01:53:42 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

char	*read_file_to_buffer(int fd, char *buf)
{
	char	*tmp_buf;
	ssize_t	bytes_read;

	tmp_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp_buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buf, '\n'))
	{
		bytes_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			free(tmp_buf);
			return (NULL);
		}
		*(tmp_buf + bytes_read) = 0;
		buf = ft_strjoin(buf, tmp_buf, 1, 0);
		if (!buf)
			break ;
	}
	free(tmp_buf);
	return (buf);
}

char	*get_line(char *buf)
{
	char	*line;
	char	*tmp_buf;

	tmp_buf = buf;
	if (!*buf)
		return (NULL);
	while (*tmp_buf && *tmp_buf != '\n')
		tmp_buf++;
	line = malloc(sizeof(char) * (tmp_buf - buf + 2));
	if (!line)
		return (NULL);
	tmp_buf -= tmp_buf - buf;
	while (*tmp_buf && *tmp_buf != '\n')
		*line++ = *tmp_buf++;
	if (*tmp_buf == '\n')
		*line++ = *tmp_buf++;
	*line = 0;
	return (line - (tmp_buf - buf));
}

char	*save_buf(char *buf)
{
	char	*tmp_buf;
	char	*n_buf;
	char	*tmpn_buf;

	tmp_buf = buf;
	while (*tmp_buf && *tmp_buf != '\n')
		tmp_buf++;
	if (!*tmp_buf)
	{
		free(buf);
		return (NULL);
	}
	n_buf = malloc(sizeof(char) * (ft_strlen(buf) - (tmp_buf - buf)));
	if (!n_buf)
		return (NULL);
	tmp_buf++;
	tmpn_buf = n_buf;
	while (*tmp_buf)
		*tmpn_buf++ = *tmp_buf++;
	*tmpn_buf = 0;
	free(buf);
	return (n_buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd == -1 && buf)
		free(buf);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf)
	{
		buf = malloc(sizeof(char) * 1);
		if (!buf)
			return (NULL);
		*buf = 0;
	}
	buf = read_file_to_buffer(fd, buf);
	if (!buf)
		return (NULL);
	line = get_line(buf);
	buf = save_buf(buf);
	return (line);
}
