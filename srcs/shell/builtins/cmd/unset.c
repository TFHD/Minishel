/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 03:17:47 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/04 07:07:46 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		lp_free(env[i++]);
	lp_free(env);
}

int	unset(t_command *cmd, t_data **data)
{
	char	**env;
	int		i;
	int		bad_args;

	if (!cmd->cmds_args[1])
		return (0);
	i = 0;
	bad_args = 0;
	while (cmd->cmds_args[++i])
	{
		if (i == -1)
		{
			ft_dprintf(2, "unset: %s: invalid parameter name\n",
				cmd->cmds_args[i]);
			bad_args = 1;
		}
		else
		{
			env = env_list_to_char((*data)->env, cmd->cmds_args[i]);
			free_env_list((*data)->env);
			(*data)->env = copy_env(env);
			free_env(env);
		}
	}
	return (bad_args);
}
