/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:14:46 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/14 21:07:29 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include <fcntl.h>
#include <unistd.h>

int	close_dup(int save_stdout)
{
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	return (0);
}

int	redirect_out_add(char *out_file, int type)
{
	int	fd;

	fd = open(out_file, O_WRONLY | O_CREAT | type, 0644);
	if (fd < 0)
	{
		perror("error open file");
		exit(1);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(out_file);
	return (0);
}

int	redirect_in(char *in_file)
{
	int	fd;

	fd = open(in_file, O_RDONLY);
	if (fd < 0)
	{
		perror("error open file");
		exit(1);
		return(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(in_file);
	return (0);
}


int	redirect(t_command *cmd)
{
	int		savefd;
	char	*in_out_file;

	in_out_file = ft_strdup(cmd->redirection->redirect);
	savefd = dup(STDOUT_FILENO);

	if (cmd->redirection->type == TOKEN_REDIRECT_OUT)
		redirect_out_add(in_out_file, O_TRUNC);
	if (cmd->redirection->type == TOKEN_REDIRECT_IN)
		redirect_in(in_out_file);
	else if (cmd->redirection->type == TOKEN_APPEND_OUT)
		redirect_out_add(in_out_file, O_APPEND);
	//if (cmd->redirection->type == TOKEN_HEREDOC)
	//	heredoc(cmd, in_out_file);
	return (savefd);
}
