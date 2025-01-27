/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:05:24 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/23 22:50:47 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex_bonus.h"
#include "shell.h"

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
		printf("declare -x ");
		while (envp[i][j])
		{
			printf("%c", envp[i][j]);
			if (envp[i][j] == '=' && equ)
			{
				printf("\"");
				equ--;
			}
			j++;
		}
		if (!equ)
			printf("\"");
		printf("\n");
		i++;
	}
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

int	is_good_export_name(char *str)
{
	int		i;
	int		alpha;

	i = 0;
	alpha = 0;
	if (!*str || ft_strlen(str) == 0 || *str == '=')
		return (0);
	while (*(str + i) && *(str + i) != '=')
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

char **realloc_env(char **env, char *content)
{
	int	i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(content);
	new_env[i] = 0;
	free_strs(env);
	return (new_env);
}

void	modify_env(t_data *data, char *env_name, char *new_content)
{
	char *final_content;
	char **env;

	final_content = ft_strsjoin(0, 3, env_name, "=", new_content);
	env = env_list_to_char(data->env, 0);
	env = realloc_env(env, final_content);
	free_env_list(data->env);
	data->env = copy_env(env);
	free_strs(env);
	free(final_content);

}

void	add_export(char *str, t_data *data)
{
	int		i;
	char	*is_inside_env;
	char	*env_name;
	char	*new_content;

	i = 0;
	while (*(str + i) && *(str + i) != '=')
		i++;
	env_name = ft_substr(str, 0, i);
	new_content = ft_substr(str, i + 1, ft_strlen(str));
	is_inside_env = get_env(data->env, env_name);
	if (is_inside_env != NULL)
		set_env(data->env, env_name, new_content);
	else
		modify_env(data, env_name, new_content);
	free(env_name);
	free(new_content);
}

int export(t_data **data, t_command *cmd)
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
			write(2, "joyshell: export: `", 20);
			write(2, *(cmd->cmds_args + i), ft_strlen(*(cmd->cmds_args + i)));
			write(2, "': not a valid identifier\n", 26);
			exit_error = 1;
		}
		add_export(*(cmd->cmds_args + i), (*data));
	}
	return (exit_error);
}
