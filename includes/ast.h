/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:18:55 by albernar          #+#    #+#             */
/*   Updated: 2025/01/28 05:59:01 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
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

typedef struct s_ast
{
	t_token_type	type;
	int				is_subshell;
	t_command		*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// AST TREE
int			add_ast_leaf(t_ast *root, t_ast *node);
int			add_ast_branch(t_ast **root, t_ast *node);
void		add_ast_node(t_ast **root, t_ast *node);
t_ast		*create_ast(t_token	**token);
void		free_ast(t_ast *ast);

// COMMAND BUILDER
t_command	*command_builder(t_token **token);
void		free_command(t_command *cmd);

// REDIRECTION LIST
void		add_redirect_node(t_redirection **head, t_token *token);
void		free_redirection(t_redirection *redir);

#endif
