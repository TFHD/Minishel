/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:05:24 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/01 03:05:51 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **envp)
{
	size_t	i;
	size_t	j;
	char	equ;

	i = 0;
	while (envp[i])
	{
		equ = 1;
		j = 0;
		ft_printf("declare -x ");
		while (envp[i][j])
		{
			ft_printf("%c", envp[i][j]);
			if (envp[i][j] == '=' && equ)
			{
				ft_printf("\"");
				equ--;
			}
			j++;
		}
		if (!equ)
			ft_printf("\"");
		ft_printf("\n");
		i++;
	}
}

void	add_export(char *str, t_data *data)
{
	int		i;
	char	*is_inside_env;
	char	*env_name;
	char	*new_content;
	int		is_plus;

	i = 0;
	is_plus = 0;
	while (*(str + i) && *(str + i) != '=' && *(str + i) != '+')
		i++;
	if (*(str + i) == '+')
		is_plus = 1;
	env_name = lp_substr(str, 0, i);
	new_content = lp_substr(str, i + 1, ft_strlen(str));
	is_inside_env = get_env(data->env, env_name);
	if (is_inside_env != NULL)
		set_env(data->env, env_name, new_content);
	else
		modify_env(data, env_name, new_content, is_plus);
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
		if (!is_good_export_name(*(cmd->cmds_args + 1)))
		{
			ft_dprintf(2, "joyshell: export: `%s': not a valid identifier\n",
				*(cmd->cmds_args + i));
			exit_error = 1;
		}
		add_export(*(cmd->cmds_args + i), (*data));
	}
	return (exit_error);
}
