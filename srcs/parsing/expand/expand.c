/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:59:51 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/11 19:19:07 by sabartho         ###   ########.fr       */
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
	free(env_name);
	if (!env)
		return (ft_strdup(""));
	return (ft_strdup(env));
}

int	get_size_s_recieved(int exit_error)
{
	int	i;

	if (!exit_error)
		return (1);
	i = 0;
	while (exit_error != 0)
	{
		exit_error /= 10;
		i++;
	}
	return (i);
}

char *get_exit_error_in_char(int exit_error)
{
	int		size;
	char	*s_return;

	size = get_size_s_recieved(exit_error);
	s_return = malloc(sizeof(char) * size + 1);
	s_return[size] = 0;
	size--;
	while (size >= 0)
	{
		s_return[size--] = exit_error % 10 + 48;
		exit_error /= 10;
	}
	return (s_return);
}

char	*replace(const char *str, char *expand, char *env_name, int i, t_data *data)
{
	char	*replace;
	char	*after_env;
	int		len_env_name;

	len_env_name = 1;
	while (ft_isalnum(*(env_name + len_env_name)))
		len_env_name++;
	if (*(env_name + 1) == '?')
	{
		replace = get_exit_error_in_char(data->exit_code);
		len_env_name++;
	}
	else
		replace = ft_substr(str, 0, i);
	after_env = ft_substr(str, i + len_env_name, ft_strlen(str) - len_env_name);
	replace = ft_strjoin(replace, expand, 1, 0);
	replace = ft_strjoin(replace, after_env, 1, 1);
	free((char *)str);
	return (replace);
}

void	extends(char **sub_string, char quote, char quote_after_type, t_data *data)
{
	int		i;
	char	*env;

	i = 0;
	while (i < (int)ft_strlen(*sub_string))
	{
		if (*(*sub_string + i) == '$' && quote == '\"')
		{
			if (ft_isalnum(*(*sub_string + i + 1)) || quote_after_type == '\'' || *(*sub_string + i + 1) == '?')
			{
				env = get_envp(*sub_string + i);
				*sub_string = replace(*sub_string, env, *sub_string + i, i, data);
				i += ft_strlen(env);
				free(env);
			}
		}
		i++;
	}
}
