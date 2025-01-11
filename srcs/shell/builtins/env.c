/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 04:23:56 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/14 22:46:02 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_command *cmd, t_data *data)
{
	int i;
	char**env;

	i = 0;
	if (*(cmd->cmds_args + 1))
	{
		no_option(cmd);
		printf("env: usage: env\n");
		exit(125);
		return (125);
	}
	env = env_list_to_char(data->env, 0);
	while (*(env + i))
	{
		printf("%s\n", *(env + i));
		free(*(env + i++));
	}
	free(env);
	exit(0);
	return (0);
}
