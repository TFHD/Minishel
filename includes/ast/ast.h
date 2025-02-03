/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:27:18 by albernar          #+#    #+#             */
/*   Updated: 2025/02/03 01:02:36 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "token.h"
# include "command_builder.h"

typedef struct s_ast
{
	t_token_type	type;
	int				is_subshell;
	t_command		*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

int			add_ast_leaf(t_ast *root, t_ast *node);
int			add_ast_branch(t_ast **root, t_ast *node);
void		add_ast_node(t_ast **root, t_ast *node);
t_ast		*create_ast(t_token	**token);
void		free_ast(t_ast *ast);

#endif
