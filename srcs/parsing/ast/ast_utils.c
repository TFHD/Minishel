/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:28:39 by albernar          #+#    #+#             */
/*   Updated: 2025/01/30 07:22:06 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	add_ast_branch_left_or_subshell(t_ast **root, t_ast *node)
{
	if ((*root)->is_subshell == 1 && node)
	{
		node->left = *root;
		*root = node;
	}
	else
	{
		if (node && !node->left)
		{
			node->left = *root;
			*root = node;
		}
		else if (!add_ast_branch(&(*root)->left, node))
			return (0);
		return (1);
	}
	return (0);
}

int	add_ast_leaf(t_ast *root, t_ast *node)
{
	if (!root->left)
	{
		root->left = node;
		return (1);
	}
	if (!root->right)
	{
		root->right = node;
		return (1);
	}
	if (root->left->type >= TOKEN_PIPE && root->left->is_subshell != 1)
		if (add_ast_leaf(root->left, node))
			return (1);
	if (root->right->type >= TOKEN_PIPE && root->right->is_subshell != 1)
		if (add_ast_leaf(root->right, node))
			return (1);
	return (0);
}

int	add_ast_branch(t_ast **root, t_ast *node)
{
	if (!*root)
		return (0);
	if (node && (node->type == TOKEN_PIPE && ((*root)->type == TOKEN_LOGICAL_AND
				|| (*root)->type == TOKEN_LOGICAL_OR))
		&& (*root)->is_subshell != 1)
	{
		if (!(*root)->right)
			(*root)->right = node;
		else
		{
			if (!add_ast_branch(&(*root)->right, node))
				return (0);
		}
		return (1);
	}
	else
	{
		if (!add_ast_branch_left_or_subshell(root, node))
			return (0);
		return (1);
	}
	return (0);
}

void	add_ast_node(t_ast **root, t_ast *node)
{
	if (!*root)
	{
		*root = node;
		return ;
	}
	if (node && ((node->type == TOKEN_LOGICAL_AND || node->type == TOKEN_LOGICAL_OR)
		&& (*root)->type <= TOKEN_ARGUMENT))
	{
		node->left = *root;
		*root = node;
		return ;
	}
	if (node && (node->type <= TOKEN_ARGUMENT || node->is_subshell == 1))
	{
		add_ast_leaf(*root, node);
		return ;
	}
	add_ast_branch(root, node);
}
