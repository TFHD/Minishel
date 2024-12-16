/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:05:24 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/15 00:10:16 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

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
	not_command(&path);
	return (path);
}

int	cmd_exist(char **path_command, t_data *data, t_command *cmd)
{
	*path_command = 0;
	
	if (is_builtins(data, cmd))
		return (1);
	if (!ft_strchr(*cmd->cmds_args, '/') && ft_strlen(*cmd->cmds_args))
		*path_command = get_executable_file(*cmd->cmds_args, 0, 0);
	else if (ft_strchr(*cmd->cmds_args, '/') && ft_strlen(*cmd->cmds_args))
		*path_command = ft_strdup(*cmd->cmds_args);
	else
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

char	**env_list_to_char(t_env_list *head)
{
	char		**envp;
	t_env_list	*current;
	t_env_list	*tmp;
	int			i;

	i = 1;
	current = head->next;
	while (current != head)
	{
		current = current->next;
		i++;
	}
	envp = malloc(sizeof(char *) * i + 1);
	current = head->next;
	i = 0;
	while (current != head)
	{
		tmp = current;
		current = current->next;
		envp[i++] = ft_strdup(tmp->content);
	}
	envp[i] = 0;
	return (envp);
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
	if (*ast->cmd->cmds_args && !cmd_exist(&path_command, data, ast->cmd))
	{
		env = env_list_to_char(data->env);
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0 && path_command)
		{
			signal(SIGINT, signal2);
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

void	exec(t_ast *ast, int tab, t_data **data)
{
	char	*t;

	if (!ast)
		return ;
	exec(ast->left, tab + 8, data);
	t = calloc(tab + 1, 1);
	if (t)
		memset(t, ' ', tab);
	exec_order(ast, *data);
	free(t);
	exec(ast->right, tab + 8, data);
}

