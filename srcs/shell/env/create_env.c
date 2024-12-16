/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:09:33 by albernar          #+#    #+#             */
/*   Updated: 2024/12/10 17:05:44 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env_list	*create_env(void)
{
	t_env_list	*env_list;
	t_env_list	*node;
	char		*pwd[2];
	char		cwd[4096];

	env_list = NULL;
	getcwd(cwd, sizeof(cwd));
	pwd[0] = lp_strdup("OLDPWD=");
	pwd[1] = lp_alloc(sizeof(char), ft_strlen(cwd) + 5);
	ft_strcpy(pwd[1], "PWD=");
	ft_strcat(pwd[1], cwd);
	node = create_env_node(pwd[0]);
	add_env_node(&env_list, node);
	node = create_env_node(pwd[1]);
	add_env_node(&env_list, node);
	return (env_list);
}

t_env_list	*copy_env(char **envp)
{
	t_env_list	*env_list;
	t_env_list	*node;
	char		*env_value;
	int			i;

	env_list = NULL;
	if (!envp || !*envp)
		env_list = create_env();
	else
	{
		i = 0;
		while (envp[i])
		{
			env_value = lp_strdup(envp[i]);
			node = create_env_node(env_value);
			add_env_node(&env_list, node);
			i++;
		}
	}
	return (env_list);
}
