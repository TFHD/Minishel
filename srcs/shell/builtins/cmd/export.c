/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:05:24 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/04 03:53:41 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **envp)
{
	size_t	i;
	char	*equal_sign;

	i = -1;
	while (envp[++i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			if (!*(equal_sign + 1))
				ft_printf("declare -x %.*s\n",
					(int)(equal_sign - envp[i]), envp[i]);
			else
				ft_printf("declare -x %.*s=\"%s\"\n",
					(int)(equal_sign - envp[i]), envp[i], equal_sign + 1);
		}
		else
			ft_printf("declare -x %s\n", envp[i]);
	}
}

void	add_export(char *str, t_data *data, int plus)
{
	int		i;
	char	*is_inside_env;
	char	*env_name;
	char	*new_content;

	i = 0;
	while (*(str + i) && *(str + i) != '=')
		i++;
	if (*(str + i - 1) == '+' && i--)
		plus++;
	env_name = lp_substr(str, 0, i);
	if (plus)
		new_content = lp_strsjoin(0, 2, get_env(data->env, env_name),
				lp_substr(str, i + 2, ft_strlen(str)));
	else
		new_content = lp_substr(str, i + 1, ft_strlen(str));
	is_inside_env = get_env(data->env, env_name);
	if (is_inside_env != NULL && ft_strchr(str, '='))
		set_env(data->env, env_name, new_content);
	else if (is_inside_env == NULL)
		modify_env(data, env_name, new_content);
	lp_free(env_name);
	lp_free(new_content);
}

int	export(t_data **data, t_command *cmd)
{
	int	i;
	int	exit_error;

	if (!cmd->cmds_args[1])
	{
		sort_env((*data)->env);
		return (0);
	}
	i = 0;
	exit_error = 0;
	while (*(cmd->cmds_args + ++i))
	{
		if (!is_good_export_name(*(cmd->cmds_args + i)))
		{
			ft_dprintf(2, "joyshell: export: `%s': not a valid identifier\n",
				*(cmd->cmds_args + i));
			exit_error = 1;
		}
		else
			add_export(*(cmd->cmds_args + i), (*data), 0);
	}
	return (exit_error);
}
