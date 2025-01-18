/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:48:17 by albernar          #+#    #+#             */
/*   Updated: 2024/11/16 08:36:30 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(char *message, char *file, int usage, int *tab)
{
	if (tab)
		free(tab);
	if (!usage && !message && !file)
		perror("Error");
	if (!usage && file)
	{
		write(2, "File : ", 7);
		write(2, file, ft_strlen(file));
		write(2, "\n", 1);
		perror("Error");
	}
	if (!usage && message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	if (usage == 1)
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	if (usage == 2)
		write(2, "Usage: ./pipex_bonus file1 cmd1 cmd2 cmd3 file2\n", 48);
	exit(1);
}

void	free_strs(char **strs)
{
	char	**tmp;

	tmp = strs;
	while (*tmp)
		free(*tmp++);
	free(strs);
}

void	close_files(int fd_count, ...)
{
	va_list	args;
	int		fd;
	int		i;

	va_start(args, fd_count);
	i = 0;
	while (i < fd_count)
	{
		fd = va_arg(args, int);
		if (fd != -1)
			close(fd);
		i++;
	}
	va_end(args);
}

void	free_multiple_str(int free_count, ...)
{
	va_list	args;
	void	*ptr;
	int		i;

	va_start(args, free_count);
	i = 0;
	while (i < free_count)
	{
		ptr = va_arg(args, void *);
		if (ptr)
			free(ptr);
		i++;
	}
	va_end(args);
}
