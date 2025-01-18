/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:47:13 by albernar          #+#    #+#             */
/*   Updated: 2024/11/22 01:02:16 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_child(int pipefd[2], int file[2], t_datap *data)
{
	char	*line;
	char	*buf;
	size_t	len;

	close_files(2, file[0], pipefd[0]);
	buf = NULL;
	line = get_next_line(0);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = 0;
		if (ft_strcmp(line, data->argv[2]) == 0)
		{
			free(line);
			break ;
		}
		buf = ft_strsjoin(0b100, 3, buf, line, "\n");
		free(line);
		line = get_next_line(0);
	}
	here_doc_finish(line, buf, pipefd, data);
	exit(0);
}

void	here_doc_parent(int pipefd[2], int file[2])
{
	close(pipefd[1]);
	if (dup2(pipefd[0], 0) == -1)
	{
		close_files(2, pipefd[0], file[0]);
		error_message("Error: Dup2 failed.", NULL, 0, NULL);
	}
	close(pipefd[0]);
}

void	here_doc_setup(t_datap *data, int *pipefd, int file[2])
{
	file[0] = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file[0] == -1)
		error_message(NULL, data->argv[data->argc - 1], 0, NULL);
	file[1] = file[0];
	if (pipe(pipefd) == -1)
	{
		close(file[0]);
		error_message("Error: Pipe failed.", NULL, 0, NULL);
	}
	data->tab_pid = malloc(sizeof(int) * (data->argc - 3));
	if (!data->tab_pid)
	{
		close_files(3, file[0], pipefd[0], pipefd[1]);
		error_message("Error: Malloc failed.", NULL, 0, NULL);
	}
}

void	here_doc_pipeline(int start, t_datap *data, int file[2], int pipefd[2])
{
	while (start < data->argc - 2)
		data->tab_pid[++data->pid_count] = fork_pipe(data, pipefd, file,
				data->argv[start++]);
	data->tab_pid[data->pid_count] = fork();
	if (data->tab_pid[data->pid_count] == -1)
	{
		close_files(3, pipefd[0], pipefd[1], file[0]);
		error_message("Error: Fork failed.", NULL, 0, data->tab_pid);
	}
	if (data->tab_pid[data->pid_count] == 0)
		execute_last_cmd(data->argv[data->argc - 2], data, file, pipefd);
	wait_for_children(data, data->pid_count + 1);
	close_files(3, pipefd[0], pipefd[1], file[0]);
}

void	here_doc(int start, t_datap *data)
{
	int	pipefd[2];
	int	file[2];

	here_doc_setup(data, pipefd, file);
	data->tab_pid[data->pid_count] = fork();
	if (data->tab_pid[data->pid_count] == -1)
	{
		close_files(3, pipefd[0], pipefd[1], file[0]);
		error_message("Error: Fork failed.", NULL, 0, data->tab_pid);
	}
	if (data->tab_pid[data->pid_count] == 0)
		here_doc_child(pipefd, file, data);
	else
	{
		here_doc_parent(pipefd, file);
		waitpid(data->tab_pid[data->pid_count], NULL, 0);
		close(pipefd[0]);
		here_doc_pipeline(start, data, file, pipefd);
	}
	close(file[0]);
	free(data->tab_pid);
}
