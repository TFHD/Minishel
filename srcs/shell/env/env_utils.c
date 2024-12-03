/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:46:43 by albernar          #+#    #+#             */
/*   Updated: 2024/12/03 20:04:48 by albernar         ###   ########.fr       */
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
