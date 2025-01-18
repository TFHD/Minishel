/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:05:24 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/17 00:24:30 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include <unistd.h>

char	*get_executable_file(char *file_name, int i, int start_i)
{
	char	*paths;
	char	*path;
	int		result;

	paths = getenv("PATH");
	result = 0;
	while (*(paths + i) && !result)
	{
		if (*(paths + i) == ':' || *(paths + i + 1) == 0)
		{
			if (*(paths + i + 1) == 0)
				path = ft_substr(paths, start_i, i - start_i + 1);
			else
				path = ft_substr(paths, start_i, i - start_i);
			path = set_path(paths, &path, file_name, i);
			if (path)
				result = 1;
			start_i = i + 1;
		}
		i++;
	}
	return (path);
}

int	cmd_exist(char **path_command, t_data *data, t_command *cmd)
{
	*path_command = 0;
	if (!ft_strchr(*cmd->cmds_args, '/') && ft_strlen(*cmd->cmds_args))
		*path_command = get_executable_file(*cmd->cmds_args, 0, 0);
	else if (ft_strchr(*cmd->cmds_args, '/') && ft_strlen(*cmd->cmds_args))
		*path_command = ft_strdup(*cmd->cmds_args);
	not_command(path_command);
	if (!*path_command)
	{
		data->exit_code = 127;
		return (1);
	}
	if (access(*path_command, X_OK))
	{
		perror(*path_command);
		free(*path_command);
		path_command = 0;
		data->exit_code = 126;
		return (1);
	}
	return (0);
}

char	**add_path(char **env)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_cpy = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	env_cpy[i++] = ft_strdup("PATH=/home/sacha/Desktop/42/Minishell");
	env_cpy[i] = 0;
	i = 0;
	while (env[i])
		free(env[i++]);
	return (env_cpy);
}

void	mini_pipe(t_data *data)
{
	int	i;
	
	printf("ok : %d\n", data->pipe_nb);
	if (data->pipe_nb == 0)
		i = 1;
	else
		i = 0;
    close(data->pipe[data->pipe_nb]);
	if (i == 1)
		dup2(data->pipe[i], STDOUT_FILENO);
	else
		dup2(data->pipe[i], STDIN_FILENO);
    close(data->pipe[i]);
}

void	exec_order(t_ast *ast, t_data *data)
{
	int		status;
	pid_t	pid;
	char	*path_command;
	char	**env;
	int		i;
	int		save_stdout;

	status = 0;
	i = 0;
	printf("nb pipe : %d\n", data->pipe_nb);
	printf("command : %s\n", *ast->cmd->cmds_args);
	if (data->pipe_nb != -1)
		mini_pipe(data);
	if (is_builtins(data, ast->cmd))
		return ;
	if (*ast->cmd->cmds_args && !cmd_exist(&path_command, data, ast->cmd))
	{
		env = env_list_to_char(data->env, 0);
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0 && path_command)
		{
			if (ast->cmd->redirection)
				save_stdout = redirect(ast->cmd);
			if (get_env(data->env, "PATH") == NULL)
				env = add_path(env);
			signal(SIGINT, SIG_DFL);
			execve(path_command, ast->cmd->cmds_args, env);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
			signal(SIGINT, signal_handler);
		}
		if (WIFEXITED(status) && path_command)
			data->exit_code = WEXITSTATUS(status);
		while (env[i])
			free(env[i++]);
		free(env);
		free(path_command);
		if (ast->cmd->redirection)
			close_dup(save_stdout);
	}
	if (data->pipe_nb != -1)
		close(data->pipe[data->pipe_nb]);
}

int	fork_for_sub_process(t_ast *ast, t_data ***data)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (ast->type == TOKEN_PIPE)
		pipe((*(*data))->pipe);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		if (ast->type == TOKEN_PIPE)
			(*(*data))->pipe_nb = 0;
		exec(ast->left, *data);
		exit((**data)->exit_code);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(**data)->exit_code = WEXITSTATUS(status);
	return (1);
}

void	exec(t_ast *ast, t_data **data)
{
	if (!ast)
		return ;
	if (ast->type == TOKEN_LOGICAL_AND || ast->type == TOKEN_LOGICAL_OR || ast->type == TOKEN_PIPE)
		fork_for_sub_process(ast, &data);
	exec_order(ast, *data);
	if (((*data)->exit_code == 0 && ast->type == TOKEN_LOGICAL_AND) || ((*data)->exit_code != 0 && ast->type == TOKEN_LOGICAL_OR) || (ast->type == TOKEN_PIPE))
	{
		if (ast->type == TOKEN_PIPE)
			(*data)->pipe_nb = 1;
		exec(ast->right, data);
	}
}
