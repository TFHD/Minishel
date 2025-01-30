/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:14:46 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/30 01:49:51 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredocs(char *delimiter, t_data *data)
{
	static int	i = 1;
    int			temp_fd;
	char		*line;
	int			save_in;

	ft_itoa_b(i, data->fds_here_docs[data->fds]);
	temp_fd = open(data->fds_here_docs[data->fds], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
	write(STDIN_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
    while (line != NULL)
	{
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
            break;
		write(STDIN_FILENO, "> ", 2);
        write(temp_fd, line, strlen(line));
		free(line);
		i++;
		line = get_next_line(STDIN_FILENO);
    }
	if (line == NULL)
	{
		write(STDIN_FILENO, "\n", 1);
		write(STDIN_FILENO, "joyshell: warning: here-document at line ", 41);
		ft_putnbr_fd(i++, STDIN_FILENO);
		write(STDIN_FILENO, " delimited by end-of-line (wanted `", 35);
		write(STDIN_FILENO, delimiter, ft_strlen(delimiter));
		write(STDIN_FILENO, "')\n", 3);
	}
	free(line);
	line = 0;
	save_in = dup(0);
    close(temp_fd);
    temp_fd = open(data->fds_here_docs[data->fds], O_RDONLY);
    if (temp_fd == -1)
	{
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(temp_fd, 0) == -1)
	{
        perror("dup2");
        exit(EXIT_FAILURE);
    }
	close(temp_fd);
	data->fds++;
	return (save_in);
}

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

void	clean_redir(int save_in, int save_out, int save_out2)
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

int	redirect(t_ast *ast, t_data *data, int pipe)
{
	t_token			*in_out_file;
	int				error;
	t_redirection	*redirecti;
	static int		fd_here_docs;
	(void) pipe;
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
		else if (redirecti->type == TOKEN_REDIRECT_IN)
		{
			clean_redir(data->red_in, -1, -1);
			data->red_in = redirect_in(in_out_file->value, &error);
		}
		else if (redirecti->type == TOKEN_APPEND_OUT)
		{
			clean_redir(-1, data->red_out, data->red_app);
			data->red_app = redirect_out_add(in_out_file->value, O_APPEND, &error);
		}
		if (redirecti->type == TOKEN_HEREDOC)
		{
			clean_redir(data->red_in, -1, -1);
			data->red_in = redirect_in(data->fds_here_docs[fd_here_docs], &error);
			fd_here_docs++;
		}
		free_tokens(in_out_file);
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
