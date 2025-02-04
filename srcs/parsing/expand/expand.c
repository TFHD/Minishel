/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:59:51 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/04 06:07:38 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard.h"
#include <strings.h>

char	*get_envp(t_data *data, char *str)
{
	char	*env_name;
	char	*env;
	int		i;

	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	env_name = lp_substr(str, 1, i - 1);
	env = get_env(data->env, env_name);
	lp_free(env_name);
	if (!env)
		return (0);
	return (env);
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

char	*get_exit_error_in_char(int exit_error)
{
	int		size;
	char	*s_return;

	size = get_size_s_recieved(exit_error);
	s_return = lp_alloc(sizeof(char), size + 1);
	s_return[size] = 0;
	size--;
	while (size >= 0)
	{
		s_return[size--] = exit_error % 10 + 48;
		exit_error /= 10;
	}
	return (s_return);
}

char	*replace(const char *str,
	char *env_name, int i, t_data *data)
{
	char	*replace;
	char	*after_env;
	char	*expand;
	int		len_env_name;

	expand = get_envp(data, (char *)str + i);
	len_env_name = 1;
	while (ft_isalnum(*(env_name + len_env_name))
		|| *(env_name + len_env_name) == '_')
		len_env_name++;
	if (*(env_name + 1) == '?')
		len_env_name++;
	replace = lp_substr(str, 0, i);
	after_env = lp_substr(str, i + len_env_name, ft_strlen(str) - len_env_name);
	if (*(env_name + 1) == '?')
		replace = lp_strsjoin(0b11, 2, replace,
				get_exit_error_in_char(data->exit_code));
	else
		replace = lp_strsjoin(0b10, 2, replace, expand);
	replace = lp_strsjoin(0b11, 2, replace, after_env);
	lp_free((char *)str);
	return (replace);
}

void	extends(char **sub_string, char quote,
	char quote_after_type, t_data *data)
{
	int		i;
	char	*env;

	i = -1;
	if (ft_strchr(*sub_string, '*') && quote_after_type != '\"'
		&& quote_after_type != '\'')
		expand_with_wildcards(sub_string);
	while (++i < (int)ft_strlen(*sub_string))
	{
		if (*(*sub_string + i) == '$' && quote == '\"')
		{
			if ((ft_isalnum(*(*sub_string + i + 1))
					|| quote_after_type == '\''
					|| *(*sub_string + i + 1) == '?'
					|| *(*sub_string + i + 1) == '_'))
			{
				env = get_envp(data, *sub_string + i);
				*sub_string = replace(*sub_string,
						*sub_string + i, i, data);
				i += ft_strlen(env) - 1;
			}
		}
	}
}
