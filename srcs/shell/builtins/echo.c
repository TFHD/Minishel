/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 05:30:27 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/14 05:59:24 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	option_echo(t_command *cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while ((cmd->cmds_args)[i] && (ft_strncmp((cmd->cmds_args)[i], "-n", 2) == 0))
	{
		while ((cmd->cmds_args)[i][j] && (cmd->cmds_args)[i][j] == 'n')
			j++;
		if ((cmd->cmds_args)[i][j] == 0)
			i++;
		else 
			return (1);
		j = 1;
	}
	return (i);
}

int	echo(t_command *cmd)
{
	int	i;
	int	option;

	i = option_echo(cmd);
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
	return (0);
}
