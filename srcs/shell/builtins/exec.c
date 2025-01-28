/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:05:24 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/28 00:39:50 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "token.h"

char	*get_executable_file(char *file_name, int i, int start_i, t_data *data)
{
	char	*paths;
	char	*path;
	int		result;

	paths = get_env(data->env, "PATH");
	if (!paths)
		paths = strdup("./");
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
	if (get_env(data->env, "PATH") == NULL && !ft_strchr(*cmd->cmds_args, '/'))
		*path_command = ft_strjoin("./", *cmd->cmds_args, 0, 0);
	else if (!ft_strchr(*cmd->cmds_args, '/') && ft_strlen(*cmd->cmds_args))
		*path_command = get_executable_file(*cmd->cmds_args, 0, 0, data);
	else if (ft_strchr(*cmd->cmds_args, '/') && ft_strlen(*cmd->cmds_args))
		*path_command = ft_strdup(*cmd->cmds_args);
	not_command(path_command, data);
	if (!*path_command)
		return (1);
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
	env_cpy[i++] = ft_strdup("PATH=.");
	env_cpy[i] = 0;
	i = 0;
	while (env[i])
		free(env[i++]);
	return (env_cpy);
}

void	exec_order(t_ast *ast, t_data *data)
{
	int		status;
	pid_t	pid;
	char	*path_command;
	char	**env;
	int		i;

	status = 0;
	i = 0;
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
	}
}

void	rebuilt_command(t_ast *ast, t_data *data)
{
	char *input;
	t_token *token;
	int	i;

	i = 1;
	input = ft_strdup(ast->cmd->cmds_args[0]);
	while (input && ast->cmd->cmds_args && ast->cmd->cmds_args[i])
		input = ft_strsjoin(0b100, 3, input, " ", ast->cmd->cmds_args[i++]);
	if (input)
	{
		free_command(ast->cmd);
		token = tokenize_input(input);
		data->type_parse = 1;
		parsing_quote(&token, data);
		pre_parsing(&token);
		data->type_parse = 0;
		parsing_quote(&token, data);
		ast->cmd = command_builder(&token);
	}
	free(input);
}

void	exec(t_ast *ast, t_data **data)
{
	if (!ast)
		return ;
	if (ast->type == TOKEN_LOGICAL_AND || ast->type == TOKEN_LOGICAL_OR || ast->type == TOKEN_PIPE)
		exec(ast->left, data);
	if (ast->cmd->redirection)
		redirect(ast, *data);
	else
	{
		if (*ast->cmd->cmds_args)
			rebuilt_command(ast, *data);
		exec_order(ast, *data);
	}
	if (((*data)->exit_code == 0 && ast->type == TOKEN_LOGICAL_AND) || ((*data)->exit_code != 0 && ast->type == TOKEN_LOGICAL_OR) || (ast->type == TOKEN_PIPE))
		exec(ast->right, data);
}
