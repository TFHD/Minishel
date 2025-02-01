/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:28:49 by albernar          #+#    #+#             */
/*   Updated: 2025/01/31 02:30:00 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_BUILDER_H
# define COMMAND_BUILDER_H
# include "token.h"

typedef struct s_redirection
{
	t_token_type			type;
	char					*redirect;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char			**cmds_args;
	t_redirection	*redirection;
}	t_command;

t_command	*command_builder(t_token **token);
void		free_command(t_command *cmd);

void		add_redirect_node(t_redirection **head, t_token *token);
void		free_redirection(t_redirection *redir);

#endif