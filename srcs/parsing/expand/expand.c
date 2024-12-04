/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:59:51 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/04 15:13:54 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envp(char *str)
{
	char	*env_name;
	char	*env;
	int		i;

	i = 1;
	while (ft_isalnum(str[i]))
		i++;
	env_name = ft_substr(str, 1, i - 1);
	env = getenv(env_name);
	lp_free(env_name);
	if (!env)
		return (ft_strdup(""));
	return (getenv(env_name));
}

char	*replace(const char *str, char *expand, char *env_name, int i)
{
	char	*replace;
	char	*after_env;
	int		len_env_name;

	len_env_name = 1;
	while (ft_isalnum(*(env_name + len_env_name)))
		len_env_name++;
	replace = ft_substr(str, 0, i);
	after_env = ft_substr(str, i + len_env_name, ft_strlen(str) - len_env_name);
	replace = ft_strjoin(replace, expand, 1, 0);
	replace = ft_strjoin(replace, after_env, 1, 1);
	lp_free((char *)str);
	lp_free(expand);
	return (replace);
}

void	extends(char **sub_string, char quote, char quote_after_type)
{
	int		i;
	char	*env;

	i = 0;
	while (i < (int)ft_strlen(*sub_string))
	{
		if (*(*sub_string + i) == '$' && quote == '\"')
		{
			if (ft_isalnum(*(*sub_string + i + 1)) || quote_after_type == '\'')
			{
				env = get_envp(*sub_string + i);
				*sub_string = replace(*sub_string, env, *sub_string + i, i);
				lp_free(env);
				i += ft_strlen(env);
			}
		}
		i++;
	}
}
