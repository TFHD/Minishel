/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:57:10 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 02:44:30 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_heredoc_name(char *buffer, int size)
{
	int		i;
	int		fd;
	char	value;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return ;
	buffer[0] = '.';
	read(fd, buffer + 1, size - 2);
	close(fd);
	i = 0;
	while (++i < size - 1)
	{
		if (i % 2 == 1)
		{
			value = buffer[i] & 15;
			buffer[i] = '0' + (value % 10);
		}
		else
		{
			value = buffer[i] & 31;
			buffer[i] = 'a' + (value % 26);
		}
	}
	buffer[size - 1] = 0;
}

void	clean_redir(int save_in, int save_out, int save_out2)
{
	if (save_in > 0)
	{
		dup2(save_in, 0);
		close(save_in);
	}
	if (save_out > 0)
	{
		dup2(save_out, 1);
		close(save_out);
	}
	if (save_out2 > 0)
	{
		dup2(save_out2, 1);
		close(save_out2);
	}
}
