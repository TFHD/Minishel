/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 04:23:56 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/01 00:42:08 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_command *cmd, t_data *data)
{
	int		i;
	char	**env;
	char	*equal_sign;

	i = 0;
	if (*(cmd->cmds_args + 1))
	{
		no_option(cmd);
		ft_printf("env: usage: env\n");
		exit(125);
		return (125);
	}
	env = env_list_to_char(data->env, 0);
	while (*(env + i))
	{
		equal_sign = ft_strchr(env[i], '=');
		if (!equal_sign || (equal_sign && *(equal_sign + 1) != 0))
			ft_printf("%s\n", *(env + i));
		lp_free(*(env + i++));
	}
	lp_free(env);
	exit(0);
	return (0);
}
