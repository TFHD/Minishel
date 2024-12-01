/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 08:45:27 by albernar          #+#    #+#             */
/*   Updated: 2024/11/28 15:23:59 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	get_operator_type_twochar(const char *input, t_token_type *type)
{
	if (ft_strncmp(input, "&&", 2) == 0)
	{
		if (type)
			*type = TOKEN_LOGICAL_AND;
		return (2);
	}
	else if (ft_strncmp(input, "||", 2) == 0)
	{
		if (type)
			*type = TOKEN_LOGICAL_OR;
		return (2);
	}
	else if (ft_strncmp(input, ">>", 2) == 0)
	{
		if (type)
			*type = TOKEN_APPEND_OUT;
		return (2);
	}
	else if (ft_strncmp(input, "<<", 2) == 0)
	{
		if (type)
			*type = TOKEN_HEREDOC;
		return (2);
	}
	return (-1);
}

static int	get_operator_type_onechar(const char *input, t_token_type *type)
{
	if (*input == '|')
	{
		if (type)
			*type = TOKEN_PIPE;
		return (1);
	}
	else if (*input == '<' || *input == '>')
	{
		if (type)
			*type = TOKEN_REDIRECT_IN;
		if (*input == '>')
			if (type)
				*type = TOKEN_REDIRECT_OUT;
		return (1);
	}
	else if (*input == '(' || *input == ')')
	{
		if (type)
			*type = TOKEN_SUBSHELL_OPEN;
		if (*input == ')')
			if (type)
				*type = TOKEN_SUBSHELL_CLOSE;
		return (1);
	}
	return (-1);
}

int	get_operator_type(const char *input, t_token_type *type)
{
	int	result;

	result = get_operator_type_twochar(input, type);
	if (result != -1)
		return (result);
	result = get_operator_type_onechar(input, type);
	return (result);
}

void	skip_whitespaces(const char *input, int *index)
{
	while (input[*index] && ft_iswhitespace(input[*index]))
		(*index)++;
}

t_token_type	determine_token_type(t_token *last_token)
{
	if (!last_token || last_token->type == TOKEN_PIPE
		|| last_token->type == TOKEN_LOGICAL_AND
		|| last_token->type == TOKEN_LOGICAL_OR
		|| last_token->type == TOKEN_SUBSHELL_OPEN)
		return (TOKEN_COMMAND);
	else
		return (TOKEN_ARGUMENT);
}
