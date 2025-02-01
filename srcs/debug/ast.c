/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:41:26 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 03:21:04 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_print_data_values(t_data *data)
{
	data->redirects.in = -1;
	data->redirects.append = -1;
	data->redirects.out = -1;
	ft_dprintf(2, "\n");
	ft_dprintf(2, "red_in : \e[32m%d\e[0m\n", data->redirects.in);
	ft_dprintf(2, "red out : \e[32m%d\e[0m\n", data->redirects.out);
	ft_dprintf(2, "red append : \e[32m%d\e[0m\n", data->redirects.append);
	ft_dprintf(2, "fds : \e[32m%d\e[0m\n", data->fd);
	ft_dprintf(2, "in_fd : \e[32m%d\e[0m\n", data->infile);
}

static void	__print_node(t_ast *ast, char *x)
{
	static const char		*token_redir[4] = {"<", ">", ">>", "<<"};
	static char				**token = NULL;
	static t_redirection	*red = NULL;

	if (ast && ast->type == TOKEN_PIPE)
		ft_dprintf(2, "%s%s\n", x, "|");
	else if (ast && ast->type == TOKEN_LOGICAL_AND)
		ft_dprintf(2, "%s%s\n", x, "&&");
	else if (ast && ast->type == TOKEN_LOGICAL_OR)
		ft_dprintf(2, "%s%s\n", x, "||");
	else
	{
		if (ast->cmd)
			token = ast->cmd->cmds_args;
		if (ast->cmd && ast->cmd->redirection)
			red = ast->cmd->redirection;
		ft_dprintf(2, "%s", x);
		while (token && *token)
			ft_dprintf(2, "{\e[31m%s\e[0m} ", *token++);
		ft_dprintf(2, "\n%s", x);
		while (red)
		{
			ft_dprintf(2, "[\e[33m%s\e[0m] {\e[31m%s\e[0m} ",
				token_redir[red->type - TOKEN_REDIRECT_IN], red->redirect);
			red = red->next;
		}
		ft_dprintf(2, "\n");
	}
}

void	__print_tree(t_ast *ast, int tab)
{
	char	*t;

	if (!ast)
		return ;
	__print_tree(ast->left, tab + 8);
	t = ft_calloc(tab + 1, 1);
	if (t)
		ft_memset(t, ' ', tab);
	__print_node(ast, t);
	free(t);
	__print_tree(ast->right, tab + 8);
}
