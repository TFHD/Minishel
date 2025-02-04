/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 05:46:34 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/04 09:51:03 by sabartho         ###   ########.fr       */
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

int	ft_ignorecase_strcmp(const char *s1, const char *s2)
{
	char	c1;
	char	c2;

	while (*s1 && *s2)
	{
		c1 = *s1;
		c2 = *s2;
		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 'a' - 'A';
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 'a' - 'A';
		if (c1 != c2)
			return ((unsigned char)c1 - (unsigned char)c2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_strcmp_ic(char *s1, char *s2)
{
	if (ft_ignorecase_strcmp(s1, s2) > 0)
		return (1);
	return (0);
}

void	swap_elem(char **x, char **y)
{
	char	*temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

int	partition(char **content, int start, int end)
{
	char	*pivot;
	int		start_tab;

	start_tab = start;
	pivot = content[start];
	start++;
	while (start <= end)
	{
		while (start <= end
			&& !(ft_ignorecase_strcmp(content[start], pivot) > 0))
			start++;
		while (start <= end && (ft_ignorecase_strcmp(content[end], pivot) > 0))
			end--;
		if (start < end)
			swap_elem(content + start, content + end);
	}
	swap_elem(content + start_tab, content + end);
	return (end);
}
