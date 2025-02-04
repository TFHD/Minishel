/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:39:20 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 10:28:53 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	get_command_len(t_token *token)
{
	int	size;

	size = 0;
	while (token && token->type != TOKEN_END && !(token->type >= TOKEN_PIPE
			&& token->type <= TOKEN_SUBSHELL_CLOSE))
	{
		if (token->type >= TOKEN_REDIRECT_IN && token->type <= TOKEN_HEREDOC)
		{
			token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		size++;
		token = token->next;
	}
	return (size);
}

t_command	*command_builder(t_token **tkn)
{
	int			size;
	t_command	*command;

	command = lp_alloc(sizeof(t_command), 1);
	size = 0;
	command->cmds_args = lp_alloc(sizeof(char *), get_command_len(*tkn) + 1);
	while (*tkn && (*tkn)->type != TOKEN_END && !((*tkn)->type >= TOKEN_PIPE
			&& (*tkn)->type <= TOKEN_SUBSHELL_CLOSE))
	{
		if ((*tkn)->type >= TOKEN_REDIRECT_IN
			&& (*tkn)->type <= TOKEN_HEREDOC)
		{
			add_redirect_node(&command->redirection, *tkn);
			*tkn = (*tkn)->next;
			if (*tkn)
				*tkn = (*tkn)->next;
		}
		else if ((*tkn)->type <= TOKEN_ARGUMENT)
		{
			command->cmds_args[size++] = lp_strdup((*tkn)->value);
			*tkn = (*tkn)->next;
		}
	}
	command->cmds_args[size] = NULL;
	return (command);
}

void	free_command(t_command *cmd)
{
	char	**tmp;

	if (!cmd)
		return ;
	tmp = cmd->cmds_args;
	while (tmp && *tmp)
		lp_free(*tmp++);
	tmp = cmd->cmds_args;
	lp_free(tmp);
	free_redirection(cmd->redirection);
	lp_free(cmd);
}
