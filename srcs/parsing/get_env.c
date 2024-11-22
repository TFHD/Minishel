/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 05:45:03 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 06:23:49 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	get_env(char **args, int nb_args)
{
	int		i;
	char	*env_name;
	char	*env_str;

	i = 0;
	while (i < nb_args)
	{
		if (args[i][0] == '$')
		{
			env_name = ft_strdup(args[i] + 1);
			free(args[i]);
			env_str = getenv(env_name);
			if (env_str)
				args[i] = ft_strdup(getenv(env_name));
			else
				args[i] = ft_strdup("");
			free(env_name);
		}
		i++;
	}
}
