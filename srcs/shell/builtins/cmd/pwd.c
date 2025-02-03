/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 03:40:00 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/03 09:58:04 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_data *data, t_command *cmd)
{
	if (*(cmd->cmds_args + 1) && *(*(cmd->cmds_args + 1)) == '-')
	{
		no_option(cmd);
		ft_printf("pwd: usage: pwd\n");
		exit(2);
		return (2);
	}
	ft_printf("%s\n", data->pwd);
	exit(0);
	return (0);
}
