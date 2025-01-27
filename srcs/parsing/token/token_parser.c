/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 08:44:01 by albernar          #+#    #+#             */
/*   Updated: 2025/01/27 08:48:25 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	process_operator(const char *input, int *i, t_token **head,
		t_token **last_token)
{
	t_token			*new_token;
	t_token_type	type;
	char			*op;
	int				op_len;

	op_len = get_operator_type(&input[*i], &type);
	if (op_len == -1)
		return (0);
	op = lp_alloc(sizeof(char), (op_len + 1));
	ft_strncpy(op, &input[*i], op_len);
	op[op_len] = 0;
	new_token = create_token(type, op);
	add_token(head, new_token);
	*last_token = new_token;
	*i += op_len;
	return (1);
}

static	int	process_argument(const char *input, int *i, t_token **head,
		t_token **last_token)
{
	t_token_type	type;
	char			*arg;
	t_token			*new_token;

	arg = extract_arg(input, i);
	if (!arg)
	{
		free_tokens(*head);
		return (-1);
	}
	type = determine_token_type(*last_token);
	new_token = create_token(type, arg);
	add_token(head, new_token);
	*last_token = new_token;
	return (1);
}

static void	__null_tokens(t_token **head, t_token **next)
{
	*head = NULL;
	*next = NULL;
}

t_token	*tokenize_input(const char *input)
{
	t_token				*head;
	t_token				*new_token;
	int					i;
	int					result;

	__null_tokens(&head, &new_token);
	i = 0;
	while (input && input[i])
	{
		skip_whitespaces(input, &i);
		if (!input[i])
			break ;
		result = process_operator(input, &i, &head, &new_token);
		if (result == 1)
			continue ;
		result = process_argument(input, &i, &head, &new_token);
		if (result == -1)
			return (NULL);
	}
	new_token = create_token(TOKEN_END, NULL);
	add_token(&head, new_token);
	if (!validate_token(head))
		return (NULL);
	return (head);
}
