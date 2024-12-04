/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_protector_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 05:43:58 by albernar          #+#    #+#             */
/*   Updated: 2024/11/26 06:26:03 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leak_protector.h"

t_lp_list	*lp_lstnew(void *content)
{
	t_lp_list	*result;

	result = malloc(sizeof(t_lp_list));
	if (__builtin_expect(!result, 0))
		return (NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}

t_lp_list	*lp_lstadd(t_lp_list **head, t_lp_list *new_node)
{
	t_lp_list	*prev;

	if (__builtin_expect(!head, 0))
		return (NULL);
	if (__builtin_expect(!new_node, 1))
		return (*head);
	if (__builtin_expect(!*head, 0))
		*head = new_node;
	else
	{
		prev = *head;
		while (prev->next)
			prev = prev->next;
		prev->next = new_node;
	}
	return (*head);
}

void	lp_lstdelone(t_lp_list **head, void *content)
{
	t_lp_list	*prev;
	t_lp_list	*current;
	t_lp_list	*tmp;

	prev = NULL;
	current = *head;
	while (current)
	{
		if (__builtin_expect(current->content == content, 1))
		{
			free(current->content);
			if (__builtin_expect(!prev, 0))
			{
				tmp = *head;
				*head = tmp->next;
				free(tmp);
				return ;
			}
			prev->next = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	lp_lstclear(t_lp_list **head)
{
	t_lp_list	*current;
	t_lp_list	*next;

	if (__builtin_expect(!head, 0))
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*head = NULL;
}
