/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:46:43 by albernar          #+#    #+#             */
/*   Updated: 2025/01/13 19:59:47 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_env(t_env_list *env_list, char *env_name)
{
	t_env_list	*current;
	size_t		env_name_size;

	if (!env_list)
		return (NULL);
	current = env_list->next;
	env_name_size = ft_strlen(env_name);
	while (current != env_list)
	{
		if (ft_strnstr((char *)current->content, env_name, env_name_size))
			return (current->content + env_name_size + 1);
		current = current->next;
	}
	return (NULL);
}

void	set_env(t_env_list *env_list, char *env_name, char *new)
{
	t_env_list	*current;
	size_t		env_name_size;

	if (!env_list)
		return ;
	current = env_list->next;
	env_name_size = ft_strlen(env_name);
	while (current != env_list)
	{
		if (ft_strnstr((char *)current->content, env_name, env_name_size))
		{
			lp_free(current->content);
			current->content = lp_alloc(sizeof(char *), env_name_size + ft_strlen(new) + 2);
			ft_strcpy(current->content, env_name);
			ft_strcat(current->content, "=");
			ft_strcat(current->content, new);
		}
		current = current->next;
	}
}

char	**env_list_to_char(t_env_list *head, char *remove)
{
	char		**envp;
	t_env_list	*current;
	t_env_list	*tmp;
	int			i;

	i = 1;
	current = head->next;
	while (current != head)
	{
		current = current->next;
		i++;
	}
	envp = malloc(sizeof(char *) * i + 1);
	current = head->next;
	i = 0;
	while (current != head)
	{
		tmp = current;
		current = current->next;
		if (!ft_strnstr(tmp->content, remove, ft_strlen(remove)))
			envp[i++] = ft_strdup(tmp->content);
	}
	envp[i] = 0;
	return (envp);
}

int	get_index_env(char **env, char *search)
{
	int	i;
	int	find;


	i = 0;
	find = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], search, ft_strlen(search)) == 0)
			find = 1;
		i++;
	}
	if (find == 1)
		return (i);
	return (-1);
}
