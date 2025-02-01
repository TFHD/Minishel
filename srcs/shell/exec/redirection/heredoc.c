/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:56:29 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 02:59:14 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredocs(t_token *token, t_data *data)
{
	t_token	*token_tmp;
	int		find;

	token_tmp = token;
	find = 0;
	while (token->type != TOKEN_END)
	{
		if (token->type == TOKEN_HEREDOC
			&& (token->next->type != TOKEN_END
				&& token->next->type == TOKEN_ARGUMENT))
		{
			clean_redir(data->redirects.in, -1, -1);
			data->redirects.in = heredocs(token->next->value, data);
			find = 1;
		}
		token = token->next;
	}
	token = token_tmp;
	clean_redir(data->redirects.in, -1, -1);
	data->redirects.in = -1;
}

void	expand_heredocs(char *input, t_data *data, int temp_fd)
{
	t_token	*token;
	t_token	*token_tmp;
	char	*final_input;

	token = tokenize_input(input);
	data->type_parse = 0;
	parsing_quote(&token, data, 1);
	final_input = lp_strdup(token->value);
	token_tmp = token;
	token = token->next;
	while (token && token->type != TOKEN_END)
	{
		final_input = lp_strsjoin(0b100, 3, final_input, " ", token->value);
		token = token->next;
	}
	token = token_tmp;
	free_tokens(token);
	ft_dprintf(temp_fd, "%s\n", final_input);
	lp_free(final_input);
}

void	listen_heredoc(char *delimiter, t_data *data,
	int temp_fd, t_token *_delimiter)
{
	static int	i = 1;
	char		*tmp;
	char		*line;

	tmp = readline("> ");
	line = lp_strdup(tmp);
	lp_free(tmp);
	while (line)
	{
		if (!ft_strcmp(line, _delimiter->value))
			break ;
		if (ft_strchr(delimiter, '\"'))
			ft_dprintf(2, "%s\n", line);
		else
			expand_heredocs(line, data, temp_fd);
		tmp = readline("> ");
		line = lp_strdup(tmp);
		lp_free(tmp);
	}
	if (!line)
		ft_dprintf(2, "\njoyshell: warning: here-document at line \
%d delimited by end-of-line (wanted `%s')\n", i++, delimiter);
	lp_free(line);
	free_tokens(_delimiter);
	close(temp_fd);
}

int	finish_heredoc(t_data *data, int *temp_fd)
{
	int	save_in;

	save_in = dup(0);
	if (save_in == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	*temp_fd = open(data->fds_here_docs[data->fd], O_RDONLY);
	if (*temp_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(*temp_fd, 0) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	return (save_in);
}

int	heredocs(char *delimiter, t_data *data)
{
	int			temp_fd;
	int			save_in;
	t_token		*_delimiter;

	generate_heredoc_name(data->fds_here_docs[data->fd], 11);
	_delimiter = tokenize_input(delimiter);
	parsing_quote(&_delimiter, data, 0);
	temp_fd = open(data->fds_here_docs[data->fd], O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	listen_heredoc(delimiter, data, temp_fd, _delimiter);
	save_in = finish_heredoc(data, &temp_fd);
	close(temp_fd);
	data->fd++;
	return (save_in);
}
