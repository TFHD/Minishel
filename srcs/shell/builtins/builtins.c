/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 03:17:47 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/14 23:49:46 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(t_data *data, t_command *cmd)
{
	if (!ft_strcmp(*cmd->cmds_args, "pwd"))
		data-> exit_code = pwd(cmd);
	//else if (!ft_strcmp(*cmd->cmds_args, "cd"))
	//	data->exit_code = cd(data);
	else if (!ft_strcmp(*cmd->cmds_args, "echo"))
		data->exit_code = echo(cmd);
	//else if (!ft_strcmp(*cmd->cmds_args, "export"))
	//	data->exit_code = export(data, cmd);
	else if (!ft_strcmp(*cmd->cmds_args, "env"))
		data->exit_code = env(cmd, data);
	//else if (!ft_strcmp(*cmd->cmds_args, "unset"))
	//	data->exit_code = unset(data, cmd);
	//else if (!ft_strcmp(*cmd->cmds_args, "exit"))
	//	data->exit_code = ft_exit(data, cmd);
	else if (!ft_strcmp(*cmd->cmds_args, "joy"))
			data->exit_code = print_header(WHITE_TEXT_BLACK_BG);
	else
		return (0);
	//printf("\e[1;31mABOUBAKAR\e[0m\n");
	return (1);
}
