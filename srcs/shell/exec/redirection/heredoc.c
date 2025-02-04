/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:56:29 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 05:30:15 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredocs(t_token *token, t_data *data)
{
	t_token	*token_tmp;
	int		error;

	error = validate_token(token, &token_tmp);
	while (token->type != TOKEN_END
		&& token_is_before_invalid_token(token, token_tmp))
	{
		if (token->type == TOKEN_HEREDOC
			&& (token->next->type != TOKEN_END
				&& token->next->type == TOKEN_ARGUMENT))
		{
			clean_redir(data->redirects.in, -1, -1);
			data->redirects.in = heredocs(token->next->value, data);
		}
		token = token->next;
	}
	clean_redir(data->redirects.in, -1, -1);
	data->redirects.in = -1;
	if (!error)
		return (2);
	return (0);
}

void	expand_heredocs(char *input, t_data *data, int temp_fd)
{
	extends_heredocs(&input, data);
	ft_dprintf(temp_fd, "%s\n", input);
	lp_free(input);
}

void	listen_heredoc(char *delimiter, t_data *data,
	int temp_fd, t_token *_delimiter)
{
	static int	i = 1;
	char		*tmp;
	char		*line;

	tmp = readline("> ");
	line = lp_strdup(tmp);
	free(tmp);
	while (line)
	{
		if (!ft_strcmp(line, _delimiter->value))
			break ;
		if (ft_strchr(delimiter, '\"') || ft_strchr(delimiter, '\''))
			ft_dprintf(temp_fd, "%s\n", line);
		else
			expand_heredocs(line, data, temp_fd);
		tmp = readline("> ");
		line = lp_strdup(tmp);
		free(tmp);
	}
	if (!line)
		ft_dprintf(2, "joyshell: warning: here-document at line \
%d delimited by end-of-line (wanted `%s')\n", i++, _delimiter->value);
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
		return (0);
	}
	*temp_fd = open(data->fds_here_docs[data->fd], O_RDONLY);
	if (*temp_fd == -1)
	{
		perror("open");
		return (0);
	}
	if (dup2(*temp_fd, 0) == -1)
	{
		perror("dup2");
		return (0);
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
			| O_CREAT | O_TRUNC, 0664);
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
