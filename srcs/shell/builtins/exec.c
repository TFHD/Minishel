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

int	redirect(t_command *cmd)
{
	int		fd;
	int		savefd;
	char	*in_out_file;

	in_out_file = ft_strdup(cmd->redirection->redirect);
	savefd = dup(STDOUT_FILENO);
	if (cmd->redirection->type == TOKEN_REDIRECT_OUT)
	{
		fd = open(in_out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("Erreur lors de l'ouverture du fichier de sortie");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		free(in_out_file);
		return (savefd);
	}
	if (cmd->redirection->type == TOKEN_REDIRECT_IN)
	{
		fd = open(in_out_file, O_RDONLY);
		if (fd < 0)
		{
			perror("Erreur lors de l'ouverture du fichier d'entrée");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		free(in_out_file);
		return (savefd);
	}
	if (cmd->redirection->type == TOKEN_APPEND_OUT)
	{
		fd = open(in_out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("Erreur lors de l'ouverture du fichier de sortie (append)");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		free(in_out_file);
		return (savefd);
	}
	free(in_out_file);
	return (0);
}

char **add_path(char **env)
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
	/*if (ast->type == TOKEN_PIPE)
	{
		printf("left : %s\n", *ast->left->cmd->cmds_args);
		printf("right : %s\n", *ast->right->cmd->cmds_args);
	}*/
	if (ast->cmd->redirection)
		save_stdout = redirect(ast->cmd);
	if (*ast->cmd->cmds_args && !cmd_exist(&path_command, data, ast->cmd))
	{
		env = env_list_to_char(data->env, 0);
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0 && path_command)
		{
			if (get_env(data->env, "PATH") == NULL)
				env = add_path(env);
			i = 0;
			while (env[i])
				printf("%s\n", env[i++]);
			i = 0;
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
	if (ast->cmd->redirection)
	{
		dup2(save_stdout, STDOUT_FILENO);
		close(save_stdout);
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
