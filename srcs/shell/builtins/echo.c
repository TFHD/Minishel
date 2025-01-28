/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 05:30:27 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/27 20:09:42 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	option_echo(t_command *cmd, int find, int i, int j)
{
	while ((cmd->cmds_args)[i]
			&& (ft_strncmp((cmd->cmds_args)[i], "-n", 2) == 0))
	{
		while ((cmd->cmds_args)[i][j] && (cmd->cmds_args)[i][j] == 'n')
			j++;
		if ((cmd->cmds_args)[i][j] == 0)
		{
			find = 1;
			i++;
		}
		else
		{
			if (find == 0)
				return (1);
			else
				return (i);
		}
		j = 1;
	}
	return (i);
}

int	echo(t_command *cmd)
{
	int	i;
	int	option;

	i = option_echo(cmd, 0, 1 ,1);
	option = i;
	while (cmd->cmds_args[i] && cmd->cmds_args[i + 1])
	{
		printf("%s", cmd->cmds_args[i]);
		printf(" ");
		i++;
	}
	if (cmd->cmds_args[i])
		printf("%s", cmd->cmds_args[i]);
	if (option == 1)
		printf("\n");
	exit(0);
	return (0);
}
