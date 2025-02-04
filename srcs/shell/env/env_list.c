/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:13:22 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 09:34:18 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env_list	*create_env_node(void *content)
{
	t_env_list	*new_node;

	new_node = lp_alloc(sizeof(t_env_list), 1);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_node(t_env_list **head, t_env_list *new_node)
{
	t_env_list	*temp;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	free_env_list(t_env_list *head)
{
	t_env_list	*current;
	t_env_list	*tmp;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->content)
			lp_free(tmp->content);
		lp_free(tmp);
	}
}
