/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:20:12 by albernar          #+#    #+#             */
/*   Updated: 2024/11/28 18:42:27 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	check_logical_operator(t_token *current, t_token *previous)
{
	if (current->type == TOKEN_LOGICAL_AND || current->type == TOKEN_LOGICAL_OR)
	{
		if (!previous)
		{
			fprintf(stderr, SYNTAX_ERROR "unexpected token near `%s'\n",
				current->value);
			return (0);
		}
		if (!current->next || (current->next->type > TOKEN_ARGUMENT
				&& current->next->type != TOKEN_SUBSHELL_OPEN))
		{
			fprintf(stderr, SYNTAX_ERROR "unexpected token near `%s'\n",
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
			fprintf(stderr, SYNTAX_ERROR "unexpected token near `%s'\n",
				current->value);
			return (0);
		}
		if (!current->next || (current->next->type > TOKEN_ARGUMENT
				&& current->next->type != TOKEN_SUBSHELL_OPEN))
		{
			fprintf(stderr, SYNTAX_ERROR "unexpected token near `%s'\n",
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
			fprintf(stderr, SYNTAX_ERROR "unexpected token near `%s'\n",
				curr->value);
			return (0);
		}
	}
	if (curr->type == TOKEN_REDIRECT_OUT || curr->type == TOKEN_APPEND_OUT)
	{
		if (!curr->next || curr->next->type != TOKEN_ARGUMENT)
		{
			fprintf(stderr, SYNTAX_ERROR "unexpected token near `%s'\n",
				curr->value);
			return (0);
		}
	}
	return (1);
}

static int	check_subshell(t_token *current)
{
	int	subshell;

	subshell = 0;
	while (current)
	{
		if (current->type == TOKEN_SUBSHELL_OPEN)
			subshell++;
		else if (current->type == TOKEN_SUBSHELL_CLOSE)
			subshell--;
		if (subshell <= -1)
		{
			fprintf(stderr, SYNTAX_ERROR "unexpected token near `%s'\n",
				current->value);
			return (0);
		}
		current = current->next;
	}
	if (subshell != 0)
		fprintf(stderr, SYNTAX_ERROR "unmatched `('\n");
	return (subshell == 0);
}

int	validate_token(t_token *token)
{
	t_token	*current;
	t_token	*previous;

	current = token;
	previous = NULL;
	if (!check_subshell(current))
		return (0);
	while (current)
	{
		if (!check_logical_operator(current, previous))
			return (0);
		else if (!check_pipe(current, previous))
			return (0);
		else if (!check_redirect(current))
			return (0);
		previous = current;
		current = current->next;
	}
	return (1);
}
