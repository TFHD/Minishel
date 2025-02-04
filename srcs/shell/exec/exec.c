/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:05:24 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/04 08:41:16 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_executable_file(char *file_name, int i, int start_i, t_data *data)
{
	char	*paths;
	char	*path;
	int		result;

	paths = get_env(data->env, "PATH");
	if (!paths)
		paths = lp_strdup("./");
	result = 0;
	while (*(paths + i) && !result)
	{
		if (*(paths + i) == ':' || *(paths + i + 1) == 0)
		{
			if (*(paths + i + 1) == 0)
				path = lp_substr(paths, start_i, i - start_i + 1);
			else
				path = lp_substr(paths, start_i, i - start_i);
			path = set_path(paths, &path, file_name, i);
			if (path)
				result = 1;
			start_i = i + 1;
		}
		i++;
	}
	return (path);
}

void	rebuilt_command(t_ast *ast, t_data *data)
{
	char	*input;
	t_token	*token;
	int		i;

	i = 1;
	input = lp_strdup(ast->cmd->cmds_args[0]);
	while (input && ast->cmd->cmds_args && ast->cmd->cmds_args[i])
		input = lp_strsjoin(0b100, 3, input, " ", ast->cmd->cmds_args[i++]);
	if (input)
	{
		free_command(ast->cmd);
		token = tokenize_input(input);
		data->type_parse = 1;
		parsing_quote(&token, data, 1);
		pre_parsing(&token);
		data->type_parse = 0;
		parsing_quote(&token, data, 1);
		ast->cmd = command_builder(&token);
	}
	lp_free(input);
}

static void	child_pipe_process(t_ast *ast, t_data *data, int is_pipe)
{
	if (data->infile != 0)
	{
		if (dup2(data->infile, 0) == -1)
		{
			perror("dup2");
			return ;
		}
		close(data->infile);
	}
	if (is_pipe != -1)
	{
		if (dup2(data->pipefd[1], 1) == -1)
		{
			perror("dup2");
			return ;
		}
	}
	child_pipe_finish(ast, data);
}

void	waitall(t_data *data)
{
	int	status;
	int	tmp;

	status = 0;
	tmp = data->pipe_fds - 1;
	while (--data->pipe_fds >= 0)
	{
		waitpid(data->pipe_list[data->pipe_fds], &status, 0);
		if (WIFEXITED(status) && data->pipe_fds == tmp)
			data->exit_code = WEXITSTATUS(status);
	}
	data->pipe_fds = 0;
}

void	do_pipe(t_ast *ast, t_data *data, int is_pipe)
{
	pid_t	pid;
	int		status;

	status = 0;
	pipe(data->pipefd);
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		child_pipe_process(ast, data, is_pipe);
	}
	else
	{
		data->pipe_list[data->pipe_fds++] = pid;
		close(data->pipefd[1]);
		if (data->infile != 0)
			close(data->infile);
		data->infile = data->pipefd[0];
	}
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
}
