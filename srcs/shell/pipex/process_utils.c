/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:49:09 by albernar          #+#    #+#             */
/*   Updated: 2024/11/16 08:45:28 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_envpath(char *cmd, char **envp)
{
	char	**paths;
	char	**tmp_paths;
	char	*path;

	while (*envp && !ft_strnstr(*envp, "PATH", 4))
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	tmp_paths = paths;
	while (*tmp_paths)
	{
		path = ft_strjoin(ft_strjoin(*tmp_paths, "/", 0, 0), cmd, 1, 0);
		if (path && !access(path, F_OK) && !access(path, X_OK))
		{
			free_strs(paths);
			return (path);
		}
		free(path);
		tmp_paths++;
	}
	free_strs(paths);
	return (NULL);
}

void	execve_command(char *cmd, t_datap *data, int file[2])
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_pipexsplit(cmd, ' ');
	if (!cmd_args)
	{
		close_files(2, file[0], file[1]);
		error_message("Error: Split failed.", NULL, 0, NULL);
	}
	if (!access(cmd_args[0], F_OK) && !access(cmd_args[0], X_OK))
		cmd_path = cmd_args[0];
	else
		cmd_path = find_envpath(cmd_args[0], data->envp);
	if (!cmd_path)
	{
		close_files(2, file[0], file[1]);
		free_strs(cmd_args);
		error_message("Error: No path found.", NULL, 0, NULL);
	}
	execve(cmd_path, cmd_args, data->envp);
	close_files(2, file[0], file[1]);
	free(cmd_path);
	free_strs(cmd_args);
	error_message("Error: Execve failed.", NULL, 0, NULL);
}
