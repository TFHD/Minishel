/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:39:20 by albernar          #+#    #+#             */
/*   Updated: 2024/12/05 16:48:05 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	get_command_len(t_token *token)
{
	int	size;

	size = 0;
	while (token->type != TOKEN_END
		&& !(token->type >= TOKEN_PIPE && token->type <= TOKEN_SUBSHELL_CLOSE))
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

t_command	*command_builder(t_token **token)
{
	int			size;
	t_command	*command;

	command = lp_alloc(sizeof(t_command), 1);
	size = 0;
	command->cmds_args = lp_alloc(sizeof(char *), get_command_len(*token) + 1);
	while ((*token)->type != TOKEN_END && !((*token)->type >= TOKEN_PIPE
			&& (*token)->type <= TOKEN_SUBSHELL_CLOSE))
	{
		if ((*token)->type <= TOKEN_ARGUMENT)
		{
			command->cmds_args[size++] = lp_strdup((*token)->value);
			*token = (*token)->next;
		}
		else if ((*token)->type >= TOKEN_REDIRECT_IN
			&& (*token)->type <= TOKEN_HEREDOC)
		{
			add_redirect_node(&command->redirection, *token);
			*token = (*token)->next;
			if (*token)
				*token = (*token)->next;
		}
	}
	return (command);
}

void	free_command(t_command *cmd)
{
	char		**tmp;

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
