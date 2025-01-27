/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:14:46 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/27 07:11:48 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "token.h"
#include <fcntl.h>
#include <unistd.h>

int	redirect_out_add(char *out_file, int type, int *error)
{
	int	fd;
	int	save_out;

	fd = open(out_file, O_WRONLY | O_CREAT | type, 0644);
	if (fd < 0)
	{
		perror("open");
		*error = 1;
		return (-1);
	}
	save_out = dup(1);
	close(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (save_out);
}

int	redirect_in(char *in_file, int *error)
{
	int	fd;
	int	save_in;

	fd = open(in_file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		*error = 1;
		return(-1);
	}
	save_in = dup(0);
	close(0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (save_in);
}

static void	clean_redir(int save_in, int save_out, int save_out2)
{
	if (save_in > 0)
	{
		dup2(save_in, 0);
		close(save_in);
	}
	if (save_out > 0)
	{
		dup2(save_out, 1);
		close(save_out);
	}
	if (save_out2 > 0)
	{
		dup2(save_out2, 1);
		close(save_out2);
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
		parsing_quote(&in_out_file, data);
		if (redirecti->type == TOKEN_REDIRECT_OUT)
		{
			clean_redir(-1, data->red_out, -1);
			data->red_out = redirect_out_add(in_out_file->value, O_TRUNC, &error);
		}
		if (redirecti->type == TOKEN_REDIRECT_IN)
		{
			clean_redir(data->red_in, -1, -1);
			data->red_in = redirect_in(in_out_file->value, &error);
		}
		if (redirecti->type == TOKEN_APPEND_OUT)
		{
			clean_redir(-1, -1, data->red_app);
			data->red_app = redirect_out_add(in_out_file->value, O_APPEND, &error);
		}
		free_tokens(in_out_file);
		//if (cmd->redirection->type == TOKEN_HEREDOC)
			//	heredoc(cmd, in_out_file);
		redirecti = redirecti->next;
		if (error)
			break;
	}
	data->exit_code = error;
	if (error != 1)
	{
		rebuilt_command(ast, data);
		exec_order(ast, data);
	}
	clean_redir(data->red_in, data->red_out, data->red_app);
	return (0);
}
