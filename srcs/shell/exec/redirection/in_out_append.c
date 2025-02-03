/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:57:30 by albernar          #+#    #+#             */
/*   Updated: 2025/02/03 09:50:59 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_out_add(char *out_file, int type, int *error)
{
	int	fd;
	int	save_out;

	fd = open(out_file, O_WRONLY | O_CREAT | type, 0644);
	if (fd < 0)
	{
		perror("open");
		*error = 1;
		return (-1);
	}
	save_out = dup(1);
	if (save_out == -1)
	{
		perror("dup");
		return (1);
	}
	close(1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(fd);
	return (save_out);
}

int	redirect_in(char *in_file, int *error)
{
	int	fd;
	int	save_in;

	fd = open(in_file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		*error = 1;
		return (-1);
	}
	save_in = dup(0);
	if (save_in == -1)
	{
		perror("dup");
		return (1);
	}
	close(0);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(fd);
	return (save_in);
}
