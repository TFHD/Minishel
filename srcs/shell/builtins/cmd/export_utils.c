/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:03:00 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 20:36:00 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_good_export_name(char *str)
{
	int		i;
	int		alpha;

	i = 0;
	alpha = 0;
	if (!*str || ft_strlen(str) == 0 || *str == '=')
		return (0);
	while (*(str + i) && (*(str + i) != '='
			&& (*(str + i) != '+' && *(str + i + 1) != '=')))
	{
		if (ft_isalpha(*(str + i)))
			alpha = 1;
		else
		{
			if (ft_isdigit(*(str + i)) && !alpha)
				return (0);
			else if (!ft_isdigit(*(str + i)) && *(str + i) != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

void	sort_env(t_env_list *env)
{
	char	**envp;
	char	*tmp;
	size_t	i;
	size_t	j;

	envp = env_list_to_char(env, 0);
	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_export(envp);
	free_strs(envp);
}

char	**realloc_env(char **env, char *content)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = lp_alloc(sizeof(char *), (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = lp_strdup(env[i]);
		i++;
	}
	new_env[i++] = lp_strdup(content);
	new_env[i] = 0;
	free_strs(env);
	return (new_env);
}

void	modify_env(t_data *data, char *env_name, char *new_content, int is_plus)
{
	char	*final_content;
	char	**env;

	if (!is_plus)
		final_content = lp_strsjoin(0, 3, env_name, "=", new_content);
	else
		final_content = lp_strsjoin(0, 4, env_name, "=",
				get_env(data->env, env_name), new_content);
	env = env_list_to_char(data->env, 0);
	env = realloc_env(env, final_content);
	free_env_list(data->env);
	data->env = copy_env(env);
	free_strs(env);
	lp_free(final_content);
}
