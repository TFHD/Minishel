/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 03:40:00 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/14 04:21:17 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	pwd(t_command *cmd)
{
	char	cwd[1024];
	if (*(cmd->cmds_args + 1))
	{
		no_option(cmd);
		printf("pwd: usage: pwd\n");
		return(2);
	}
	printf("%s\n", getcwd(cwd, 1024));
	return (0);
}
