/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:13:22 by albernar          #+#    #+#             */
/*   Updated: 2024/11/27 09:22:35 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env_list	*create_env_node(void *content)
{
	t_env_list	*new_node;

	new_node = lp_alloc(sizeof(t_env_list), 1);
	new_node->content = content;
	new_node->next = new_node;
	new_node->prev = new_node;
	return (new_node);
}

void	add_env_node(t_env_list **head, t_env_list *new_node)
{
	t_env_list	*tail;

	if (!*head)
		*head = new_node;
	else
	{
		tail = (*head)->prev;
		tail->next = new_node;
		new_node->prev = tail;
		new_node->next = *head;
		(*head)->prev = new_node;
	}
}

void	free_env_list(t_env_list *head)
{
	t_env_list	*current;
	t_env_list	*tmp;

	if (!head)
		return ;
	current = head->next;
	while (current != head)
	{
		tmp = current;
		current = current->next;
		if (tmp->content)
			lp_free(tmp->content);
		lp_free(tmp);
	}
	lp_free(head->content);
	lp_free(head);
}
