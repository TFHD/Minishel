/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:37:37 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 03:20:42 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_token_type_name(t_token_type type)
{
	static const char	*token_type_names[] = {
		"TOKEN_COMMAND",
		"TOKEN_ARGUMENT",
		"TOKEN_PIPE",
		"TOKEN_LOGICAL_AND",
		"TOKEN_LOGICAL_OR",
		"TOKEN_SUBSHELL_OPEN",
		"TOKEN_SUBSHELL_CLOSE",
		"TOKEN_REDIRECT_IN",
		"TOKEN_REDIRECT_OUT",
		"TOKEN_APPEND_OUT",
		"TOKEN_HEREDOC",
		"TOKEN_END"
	};

	if (type >= 0 && type <= TOKEN_END)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void	print_tokens(t_token *head)
{
	t_token	*current;
	int		index;

	index = 0;
	if (!head)
	{
		ft_dprintf(2, "No tokens to display.\n");
		return ;
	}
	current = head;
	while (current)
	{
		ft_dprintf(2, "Token %d: Type = \e[31m%s\e[0m, Value = %s\n",
			index++,
			get_token_type_name(current->type),
			current->value
			);
		current = current->next;
	}
}
