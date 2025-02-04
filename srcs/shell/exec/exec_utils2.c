/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:42:47 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 07:05:23 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strs(char **strs)
{
	char	**tmp;

	tmp = strs;
	while (*tmp)
		lp_free(*tmp++);
	lp_free(strs);
}

void	unlink_fd(t_data *data)
{
	int	tmp_fd;

	tmp_fd = data->fd;
	while (--data->fd >= 0)
		unlink(data->fds_here_docs[data->fd]);
	data->fd = tmp_fd;
}

static void	not_command3(char **path, t_data *data, struct stat st)
{
	if (S_ISDIR(st.st_mode))
	{
		if (ft_strchr(*path, '/'))
		{
			ft_dprintf(2, "%s: Is a directory\n", (*path));
			lp_free(*path);
			*path = NULL;
			data->exit_code = 126;
		}
		else
		{
			ft_dprintf(2, "%s: command not found\n", (*path));
			lp_free(*path);
			*path = NULL;
			data->exit_code = 127;
		}
	}
	else if (*path && !access(*path, F_OK) && !ft_strchr(*path, '/'))
	{
		ft_dprintf(2, "%s: command not found\n", (*path));
		lp_free(*path);
		*path = NULL;
		data->exit_code = 127;
	}
}

void	not_command2(char **path, t_data *data, struct stat st)
{
	if (access((*path), F_OK) || (stat(*path, &st) != 0))
	{
		if (stat(*path, &st) != 0 && ft_strchr(*path, '/'))
			ft_dprintf(2, "%s: No such file or directory\n", (*path));
		else
			ft_dprintf(2, "%s: command not found\n", (*path));
		lp_free(*path);
		*path = NULL;
		data->exit_code = 127;
	}
	else
		not_command3(path, data, st);
}

void	child_pipe_finish(t_ast *ast, t_data *data)
{
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	if (ast->cmd->redirection)
		redirect(ast, data);
	else
	{
		if (*ast->cmd->cmds_args)
			rebuilt_command(ast, data);
		exec_order(ast, data);
	}
	exit(data->exit_code);
}
