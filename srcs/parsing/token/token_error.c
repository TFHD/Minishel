/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:20:12 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 06:58:38 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	check_logical_operator(t_token *current, t_token *previous)
{
	if (current->type == TOKEN_LOGICAL_AND || current->type == TOKEN_LOGICAL_OR)
	{
		if (!previous)
		{
			ft_dprintf(2, SYNTAX_ERROR "unexpected token near `%s'\n",
				current->value);
			return (0);
		}
		if (!current->next || (current->next->type > TOKEN_ARGUMENT
				&& current->next->type != TOKEN_SUBSHELL_OPEN
				&& !(current->next->type >= TOKEN_REDIRECT_IN
					&& current->next->type <= TOKEN_HEREDOC)))
		{
			ft_dprintf(2, SYNTAX_ERROR "unexpected token near `%s'\n",
				current->value);
			return (0);
		}
	}
	return (1);
}

static int	check_pipe(t_token *current, t_token *previous)
{
	if (current->type == TOKEN_PIPE)
	{
		if (!previous)
		{
			ft_dprintf(2, SYNTAX_ERROR "unexpected token near `%s'\n",
				current->value);
			return (0);
		}
		if (!current->next || (current->next->type > TOKEN_ARGUMENT
				&& current->next->type != TOKEN_SUBSHELL_OPEN
				&& !(current->next->type >= TOKEN_REDIRECT_IN
					&& current->next->type <= TOKEN_HEREDOC)))
		{
			ft_dprintf(2, SYNTAX_ERROR "unexpected token near `%s'\n",
				current->value);
			return (0);
		}
	}
	return (1);
}

static int	check_redirect(t_token *curr)
{
	if (curr->type == TOKEN_HEREDOC || curr->type == TOKEN_REDIRECT_IN)
	{
		if (!curr->next || curr->next->type != TOKEN_ARGUMENT)
		{
			ft_dprintf(2, SYNTAX_ERROR "unexpected token near `%s'\n",
				curr->value);
			return (0);
		}
	}
	if (curr->type == TOKEN_REDIRECT_OUT || curr->type == TOKEN_APPEND_OUT)
	{
		if (!curr->next || curr->next->type != TOKEN_ARGUMENT)
		{
			ft_dprintf(2, SYNTAX_ERROR "unexpected token near `%s'\n",
				curr->value);
			return (0);
		}
	}
	return (1);
}

static int	check_subshell(t_token *c, int subsh)
{
	while (c)
	{
		if (c->type == TOKEN_SUBSHELL_OPEN)
			subsh++;
		else if (c->type == TOKEN_SUBSHELL_CLOSE)
			subsh--;
		if (((c->type == TOKEN_SUBSHELL_OPEN)
				&& c->next && (c->next->type == TOKEN_SUBSHELL_CLOSE))
			|| ((c->type == TOKEN_SUBSHELL_CLOSE)
				&& c->next && (c->next->type == TOKEN_SUBSHELL_OPEN))
			|| ((c->type == TOKEN_SUBSHELL_CLOSE)
				&& c->next && (c->next->type == TOKEN_ARGUMENT)) || subsh < 0)
		{
			ft_dprintf(2, SYNTAX_ERROR "unexpected token near `%s'\n",
				c->value);
			return (0);
		}
		c = c->next;
	}
	if (subsh != 0)
		ft_dprintf(2, SYNTAX_ERROR "unmatched `('\n");
	if (subsh != 0)
		return (0);
	return (1);
}

int	validate_token(t_token *token, t_token **token_find_error)
{
	t_token	*current;
	t_token	*previous;

	current = token;
	previous = NULL;
	if (!check_subshell(current, 0))
		return (0);
	while (current)
	{
		if (!check_logical_operator(current, previous)
			|| !check_pipe(current, previous)
			|| !check_redirect(current))
		{
			*token_find_error = current;
			return (0);
		}
		previous = current;
		current = current->next;
	}
	*token_find_error = NULL;
	return (1);
}
