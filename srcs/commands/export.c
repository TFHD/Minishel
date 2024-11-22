/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:32:43 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 08:53:30 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	is_in_env(char *str, char **envp)
{


}

void	export(char *str, char **envp)
{
	int		i;
	char	**env_tmp;

	i = 0;
	while (*(envp + i))
		i++;
	env_tmp = malloc(sizeof(char *) * (i + is_in_env(str, envp)));
	i = 0;
	while (*(envp + i))
	{
		if (!ft_strnchr(*(envp + i), str))
			*(env_tmp + i) = ft_strdup(*(envp + i));
		i++;
	}
	*(env_tmp + i++) = ft_strdup(str);
	*env_tmp = 0;
	free_args(envp);
	envp = env_tmp;
}*/
