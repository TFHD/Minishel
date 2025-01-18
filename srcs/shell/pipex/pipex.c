/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:38:51 by albernar          #+#    #+#             */
/*   Updated: 2025/01/15 21:19:57 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	init_files_tab(t_datap *data, int file[2])
{
	data->tab_pid = malloc(sizeof(int) * (data->argc - 2));
	if (!data->tab_pid)
		error_message("Error: Malloc failed.", NULL, 0, NULL);
	file[0] = open(data->argv[1], O_RDONLY);
	if (file[0] == -1)
	{
		error_message("Error: Opening input file failed.", data->argv[1], 0,
			data->tab_pid);
	}
	file[1] = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (file[1] == -1)
	{
		close(file[0]);
		error_message("Error: Opening output file failed.",
			data->argv[data->argc - 1], 0, data->tab_pid);
	}
}

void	wait_for_children(t_datap *data, int pid_count)
{
	int	i;

	i = 0;
	while (i < pid_count)
	{
		if (waitpid(data->tab_pid[i], &(data->exit_status), 0) == -1)
			if (errno != ECHILD)
				error_message("Error: Waitpid failed.", NULL, 0, data->tab_pid);
		i++;
	}
}

void	pipex(int start, t_datap *data)
{
	int	file[2];
	int	pipefd[2];

	init_files_tab(data, file);
	if (dup2(file[0], 0) == -1)
	{
		close_files(2, file[0], file[1]);
		error_message("Error: Dup2 failed on input.", NULL, 0, data->tab_pid);
	}
	while (start < data->argc - 2)
		data->tab_pid[data->pid_count++] = fork_pipe(data, pipefd, file,
				data->argv[start++]);
	data->tab_pid[data->pid_count] = fork();
	if (data->tab_pid[data->pid_count] == -1)
	{
		close_files(2, file[0], file[1]);
		error_message("Error: Fork failed.", NULL, 0, data->tab_pid);
	}
	if (data->tab_pid[data->pid_count] == 0)
		execute_last_cmd(data->argv[data->argc - 2], data, file, pipefd);
	wait_for_children(data, data->pid_count + 1);
	close_files(2, file[0], file[1]);
	free(data->tab_pid);
}
