/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:32:43 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 23:15:26 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *str)
{
	int		i;
	char	*env_name;

	i = 0;
	while (*(str + i) != '=')
		i++;
	env_name = ft_strdup(ft_substr(str, 0, i), 1);
	return (env_name);
}

int	is_in_env(char *str, char **envp)
{
	int		i;
	char	*env_name;

	i = 0;
	env_name = get_env_name(str);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], env_name, ft_strlen(env_name)))
		{
			free(env_name);
			return (1);
		}
		i++;
	}
	free(env_name);
	return (2);
}

char **export(char *str, char **envp)
{
	int		i;
	int		j;
	char	**env_tmp;
	char	*env_name;

	i = 0;
	j = 0;
	env_name = get_env_name(str);
	while (*(envp + i))
		i++;
	env_tmp = malloc(sizeof(char *) * (i + is_in_env(str, envp)));
	i = 0;
	while (*(envp + i))
	{
		if (ft_strncmp(*(envp + i), env_name, ft_strlen(env_name)))
			*(env_tmp + j++) = ft_strdup(*(envp + i), 0);
		i++;
	}
	*(env_tmp + j++) = ft_strdup(str, 0);
	*(env_tmp + j) = 0;
	free(env_name);
	return (env_tmp);
}
