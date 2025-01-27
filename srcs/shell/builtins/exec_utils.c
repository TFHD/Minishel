/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 03:15:30 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/24 19:25:01 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_path(char *paths, char **path, char *file_name, int i)
{

	*path = ft_strsjoin(0b100, 3, *path, "/", file_name);
	if (access(*path, X_OK) && *(paths + i + 1) != 0)
	{
		free(*path);
		return (NULL);
	}
	else if (*(paths + i + 1) == 0)
	{
		free(*path);
		*path = ft_strdup(file_name);
	}
	return (*path);
}

void	not_command(char **path, t_data *data)
{
	struct stat st;

	if (!*path)
	{
		write(2, ": command not found\n", 21);
		return ;
	}
	else if (access((*path), F_OK) || (stat(*path, &st) == 0 && !ft_strchr(*path, '/')))
	{
		write(2, (*path), ft_strlen((*path)));
		write(2, ": command not found\n", 21);
		free(*path);
		*path = NULL;
		data->exit_code = 127;
	}
	else if (S_ISDIR(st.st_mode))
	{
		write(2, (*path), ft_strlen((*path)));
		write(2, ": Is a directory\n", 17);
		free(*path);
		*path = NULL;
		data->exit_code = 126;
	}
}

void	no_option(t_command *cmd)
{
	printf("%s: ", *cmd->cmds_args);
	printf("%s: invalid option\n", *(cmd->cmds_args + 1));
}
