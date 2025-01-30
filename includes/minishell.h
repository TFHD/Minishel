/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:10:43 by albernar          #+#    #+#             */
/*   Updated: 2025/01/30 06:48:58 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "shell.h"
# include "token.h"
# include "ast.h"
# include "pipex_bonus.h"
# include "../lib/libft/libft.h"
# include "../srcs/leak_protector/leak_protector.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>


extern int	g_recieved;

typedef struct s_data
{
	t_token		*token;
	t_env_list	*env;
	t_ast		*ast;
	int			exit_code;
	int			type_parse;
	int			red_in;
	int			red_out;
	int			red_app;
	int			fds;
	char		fds_here_docs[1024][11];
	int			pipes[2];
	int			in_fd;
}				t_data;

void	extends(char **sub_string, char quote, char quote_after, t_data *data);
void	exec(t_ast *ast, t_data **data, int pipes);
void	exec_order(t_ast *ast, t_data *data);
char	*get_env(t_env_list *env_list, char *env_name);
void	parsing_quote(t_token **token, t_data *data, int expand);
void	pre_parsing(t_token **data);
void	signal_handler(int signal);
void	signal2(int signal);
char	*set_path(char *paths, char **path, char *file_name, int i);
void	not_command(char **path, t_data *data);
int		is_builtins(t_data *data, t_command *cmd);

char	**env_list_to_char(t_env_list *head, char *remove);
void	no_option(t_command *cmd);
int		pwd(t_command *cmd);
int		env(t_command *cmd, t_data *data);
int		echo(t_command *cmd);
int		redirect(t_ast *ast, t_data *data, int pipe);
int		ft_exit(t_command *cmd);
int		cd(t_command *cmd, t_data *data);
void	set_env(t_env_list *env_list, char *env_name, char *new);
int		unset(t_command *cmd, t_data **data);
int		close_dup(int save_stdout);
int		export(t_data **data, t_command *cmd);
int		get_index_env(char **env, char *search);
void	rebuilt_command(t_ast *ast, t_data *data);
int		heredocs(char *delimiter, t_data *data);
void	clean_redir(int save_in, int save_out, int save_out2);
void	do_pipe(t_ast *ast, t_data *data, int is_pipe);

#endif
