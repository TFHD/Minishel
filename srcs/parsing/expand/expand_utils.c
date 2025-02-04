/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 05:46:34 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/04 07:45:36 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_strcmp_ic(char *s1, char *s2)
{
	char	*low_s1;
	char	*low_s2;

	low_s1 = lp_strdup(s1);
	low_s2 = lp_strdup(s2);
	ft_strtolower(low_s1);
	ft_strtolower(low_s2);
	if (ft_strcmp(low_s1, low_s2) > 0)
		return (1);
	return (0);
}

void	sort_wilcrads(char **expand_wc)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	while (expand_wc[i])
	{
		j = i + 1;
		while (expand_wc[j])
		{
			if (ft_strcmp_ic(expand_wc[i], expand_wc[j]) > 0)
			{
				tmp = expand_wc[i];
				expand_wc[i] = expand_wc[j];
				expand_wc[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
