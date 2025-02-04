/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:14:46 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/04 07:54:10 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_parser(t_data *data, int *error,
	t_redirection *redirecti, char *value)
{
	static int	fd_here_docs;

	if (redirecti->type == TOKEN_REDIRECT_OUT)
	{
		clean_redir(-1, data->redirects.out, -1);
		data->redirects.out = redirect_out_add(value, O_TRUNC, error);
	}
	else if (redirecti->type == TOKEN_REDIRECT_IN)
	{
		clean_redir(data->redirects.in, -1, -1);
		data->redirects.in = redirect_in(value, error);
	}
	else if (redirecti->type == TOKEN_APPEND_OUT)
	{
		clean_redir(-1, data->redirects.out, data->redirects.append);
		data->redirects.append = redirect_out_add(value,
				O_APPEND, error);
	}
	if (redirecti->type == TOKEN_HEREDOC)
	{
		clean_redir(data->redirects.in, -1, -1);
		data->redirects.in = redirect_in(data->fds_here_docs[fd_here_docs++],
				error);
	}
}

int	redirect(t_ast *ast, t_data *data)
{
	t_token			*in_out_file;
	int				error;
	t_redirection	*redirecti;

	redirecti = ast->cmd->redirection;
	error = 0;
	while (redirecti)
	{
		in_out_file = tokenize_input(redirecti->redirect);
		parsing_quote(&in_out_file, data, 1);
		redirect_parser(data, &error, redirecti, in_out_file->value);
		free_tokens(in_out_file);
		redirecti = redirecti->next;
		if (error)
			break ;
	}
	data->exit_code = error;
	if (error != 1)
		rebuilt_command(ast, data);
	if (error != 1)
		exec_order(ast, data);
	clean_redir(data->redirects.in, data->redirects.out,
		data->redirects.append);
	return (0);
}
