/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:38:23 by albernar          #+#    #+#             */
/*   Updated: 2024/11/29 10:56:31 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_redirection	*create_redirection_list(t_token *token)
{
	t_redirection	*new_node;

	new_node = lp_alloc(sizeof(t_redirection), 1);
	new_node->redirect = token->next->value;
	new_node->type = token->type;
	new_node->next = NULL;
	return (new_node);
}

void	add_redirect_node(t_redirection **head, t_token *token)
{
	t_redirection	*node;
	t_redirection	*tmp;

	if (head && !*head)
		*head = create_redirection_list(token);
	else
	{
		node = create_redirection_list(token);
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	free_redirection(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		lp_free(tmp->redirect);
		lp_free(tmp);
	}
}
