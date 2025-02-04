/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:34:49 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 10:17:59 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ast.h"
# include "debug.h"
# include "command_builder.h"
# include "token.h"
# include "wildcard_bonus.h"
# include "shell.h"
# include "redirection.h"
# include "exec.h"
# include "environment.h"
# include "builtins.h"
# include "../../libft/includes/libft.h"
# include "../../srcs/leak_protector/leak_protector.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>

extern int	g_received;

typedef struct s_redirects
{
	int	in;
	int	out;
	int	append;
}	t_redirects;

typedef struct s_data
{
	char		*input;
	t_token		*token;
	t_env_list	*env;
	t_ast		*ast;
	int			exit_code;
	int			type_parse;
	t_redirects	redirects;
	int			fd;
	char		fds_here_docs[1024][11];
	int			pipe_list[8192];
	int			pipe_fds;
	int			pipefd[2];
	int			infile;
	int			expand;
	char		*pwd;
}				t_data;

void	extends(char **sub_string, char quote, char quote_after, t_data *data);
void	parsing_quote(t_token **token, t_data *data, int expand);
void	pre_parsing(t_token **data);
void	signal_handler(int signal);
void	accurate_signal(int signal, t_data *data);
char	*replace(const char *str, char *env_name, int i, t_data *data);
void	free_strs(char **strs);

#endif
