/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 05:30:27 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/01 00:33:59 by albernar         ###   ########.fr       */
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

	i = option_echo(cmd, 0, 1, 1);
	option = i;
	while (cmd->cmds_args[i] && cmd->cmds_args[i + 1])
	{
		ft_printf("%s", cmd->cmds_args[i]);
		ft_printf(" ");
		i++;
	}
	if (cmd->cmds_args[i])
		ft_printf("%s", cmd->cmds_args[i]);
	if (option == 1)
		ft_printf("\n");
	exit(0);
	return (0);
}
