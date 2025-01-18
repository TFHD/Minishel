/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 03:17:47 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/13 20:50:38 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(t_data *data, t_command *cmd, int save_stdout)
{
	if (cmd->redirection)
		redirect(cmd);
	if (!ft_strcmp(*cmd->cmds_args, "pwd"))
		data->exit_code = pwd(cmd);
	else if (!ft_strcmp(*cmd->cmds_args, "cd"))
		data->exit_code = cd(cmd, data);
	else if (!ft_strcmp(*cmd->cmds_args, "echo"))
		data->exit_code = echo(cmd);
	else if (!ft_strcmp(*cmd->cmds_args, "env"))
		data->exit_code = env(cmd, data);
	else if (!ft_strcmp(*cmd->cmds_args, "exit"))
		data->exit_code = ft_exit(cmd);
	else if (!ft_strcmp(*cmd->cmds_args, "export"))
		data->exit_code = export(data, cmd);
	else if (!ft_strcmp(*cmd->cmds_args, "unset"))
		data->exit_code = unset(cmd, &data);
	else if (!ft_strcmp(*cmd->cmds_args, "joy"))
		data->exit_code = print_header(WHITE_TEXT_BLACK_BG);
	else
		return (0);
	if (cmd->redirection)
		close_dup(save_stdout);
	return (1);
}

int	create_sub_child_builtins(t_data *data, t_command *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
		builtins(data, cmd, 0);
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	return (1);
}

int	is_builtins(t_data *data, t_command *cmd)
{
	if (!ft_strcmp(*cmd->cmds_args, "pwd")
		|| !ft_strcmp(*cmd->cmds_args, "echo")
		|| !ft_strcmp(*cmd->cmds_args, "env")
		|| !ft_strcmp(*cmd->cmds_args, "joy"))
		return (create_sub_child_builtins(data, cmd));
	else if (!ft_strcmp(*cmd->cmds_args, "exit")
		|| !ft_strcmp(*cmd->cmds_args, "cd")
		|| !ft_strcmp(*cmd->cmds_args, "unset")
		|| !ft_strcmp(*cmd->cmds_args, "export"))
	{
		builtins(data, cmd, 0);
		return (1);
	}
	return (0);
}
