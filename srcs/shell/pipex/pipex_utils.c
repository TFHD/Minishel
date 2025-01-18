/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:54:21 by albernar          #+#    #+#             */
/*   Updated: 2024/11/16 08:42:47 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_last_cmd(char *cmd, t_datap *data, int file[2], int pipefd[2])
{
	free(data->tab_pid);
	if (dup2(file[1], 1) == -1)
	{
		close_files(4, file[0], file[1], pipefd[0], pipefd[1]);
		error_message("Error: Dup2 failed on output.", NULL, 0, data->tab_pid);
	}
	close_files(2, file[0], file[1]);
	execve_command(cmd, data, file);
	exit(1);
}

int	fork_pipe(t_datap *data, int pipefd[2], int file[2], char *cmd)
{
	int	pid;

	if (pipe(pipefd) == -1)
	{
		close_files(2, file[0], file[1]);
		error_message("Error: Pipe failed.", NULL, 0, data->tab_pid);
	}
	pid = fork();
	if (pid == -1)
	{
		close_files(4, pipefd[0], pipefd[1], file[0], file[1]);
		error_message("Error: Fork failed.", NULL, 0, data->tab_pid);
	}
	if (pid == 0)
		child_process(data, pipefd, file, cmd);
	if (dup2(pipefd[0], 0) == -1)
	{
		close_files(4, pipefd[0], pipefd[1], file[0], file[1]);
		error_message("Error: Dup2 failed.", NULL, 0, data->tab_pid);
	}
	close_files(2, pipefd[0], pipefd[1]);
	return (pid);
}

void	child_process(t_datap *data, int pipefd[2], int file[2], char *cmd)
{
	free(data->tab_pid);
	if (dup2(pipefd[1], 1) == -1)
	{
		close_files(4, pipefd[0], pipefd[1], file[0], file[1]);
		error_message("Error: Dup2 failed.", NULL, 0, NULL);
	}
	close_files(4, pipefd[0], pipefd[1], file[0], file[1]);
	execve_command(cmd, data, file);
	exit(1);
}
