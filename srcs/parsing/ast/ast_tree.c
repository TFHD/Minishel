/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:21:45 by albernar          #+#    #+#             */
/*   Updated: 2025/01/27 08:21:10 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_ast	*create_ast_node(t_token **token)
{
	t_ast	*node;

	node = lp_alloc(sizeof(t_ast), 1);
	node->type = (*token)->type;
	node->cmd = command_builder(token);
	if (node->type >= TOKEN_PIPE && node->type <= TOKEN_SUBSHELL_CLOSE)
		*token = (*token)->next;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

t_ast	*create_ast(t_token **token)
{
	t_ast	*root;
	t_ast	*node;

	if (!*token)
		return (NULL);
	root = NULL;
	while (*token && ((*token)->type != TOKEN_SUBSHELL_CLOSE
			&& (*token)->type != TOKEN_END))
	{
		if ((*token)->type == TOKEN_SUBSHELL_OPEN)
		{
			*token = (*token)->next;
			node = create_ast(token);
			node->is_subshell = 1;
		}
		else
			node = create_ast_node(token);
		add_ast_node(&root, node);
	}
	if (*token && (*token)->type == TOKEN_SUBSHELL_CLOSE)
		*token = (*token)->next;
	return (root);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free_command(ast->cmd);
	free_ast(ast->left);
	free_ast(ast->right);
	lp_free(ast);
}
