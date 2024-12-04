/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 08:48:33 by albernar          #+#    #+#             */
/*   Updated: 2024/11/28 14:27:55 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = lp_alloc(sizeof(t_token), 1);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*temp;

	current = head;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->value)
			lp_free(temp->value);
		lp_free(temp);
	}
}
