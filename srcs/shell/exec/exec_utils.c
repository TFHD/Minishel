/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 03:15:30 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/04 07:08:25 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_path(char *paths, char **path, char *file_name, int i)
{
	*path = lp_strsjoin(0b100, 3, *path, "/", file_name);
	if (access(*path, X_OK) && *(paths + i + 1) != 0)
	{
		lp_free(*path);
		return (NULL);
	}
	else if (*(paths + i + 1) == 0)
	{
		lp_free(*path);
		*path = lp_strdup(file_name);
	}
	return (*path);
}

void	not_command(char **path, t_data *data)
{
	struct stat	st;

	if (!*path)
	{
		ft_dprintf(2, ": command not found\n");
		data->exit_code = 127;
		return ;
	}
	else if (stat((*path), &st) == -1
		&& ft_strchr(*path, '/') && errno == EACCES)
	{
		ft_dprintf(2, "%s: Permission denied\n", (*path));
		lp_free(*path);
		*path = NULL;
		data->exit_code = 126;
	}
	else
		not_command2(path, data, st);
}

void	no_option(t_command *cmd)
{
	ft_dprintf(2, "%s: ", *cmd->cmds_args);
	ft_dprintf(2, "%s: invalid option\n", *(cmd->cmds_args + 1));
}

int	cmd_exist(char **path_command, t_data *data, t_command *cmd)
{
	*path_command = 0;
	if (get_env(data->env, "PATH") == NULL && !ft_strchr(*cmd->cmds_args, '/'))
		*path_command = lp_strsjoin(0b00, 2, "./", *cmd->cmds_args);
	else if (!ft_strchr(*cmd->cmds_args, '/') && ft_strlen(*cmd->cmds_args))
		*path_command = get_executable_file(*cmd->cmds_args, 0, 0, data);
	else if (ft_strchr(*cmd->cmds_args, '/') && ft_strlen(*cmd->cmds_args))
		*path_command = lp_strdup(*cmd->cmds_args);
	not_command(path_command, data);
	if (!*path_command)
		return (1);
	if (access(*path_command, X_OK) && ft_strchr(*path_command, '/'))
	{
		perror(*path_command);
		lp_free(*path_command);
		path_command = 0;
		data->exit_code = 126;
		return (1);
	}
	return (0);
}
