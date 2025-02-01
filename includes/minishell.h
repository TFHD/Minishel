/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:34:49 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 03:04:32 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ast.h"
# include "debug.h"
# include "command_builder.h"
# include "token.h"
# include "wildcard.h"
# include "shell.h"
# include "../../libft/includes/libft.h"
# include "../../srcs/leak_protector/leak_protector.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>

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
	int			pipefd[2];
	int			infile;
	int			expand;
}				t_data;

void	extends(char **sub_string, char quote, char quote_after, t_data *data);
void	exec(t_ast *ast, t_data *data, int pipes);
void	exec_order(t_ast *ast, t_data *data);
char	*get_env(t_env_list *env_list, char *env_name);
void	parsing_quote(t_token **token, t_data *data, int expand);
void	pre_parsing(t_token **data);
void	signal_handler(int signal);
void	accurate_signal(int signal);
char	*set_path(char *paths, char **path, char *file_name, int i);
void	not_command(char **path, t_data *data);
int		is_builtins(t_data *data, t_command *cmd);
int		cmd_exist(char **path_command, t_data *data, t_command *cmd);
char	*get_executable_file(char *file_name, int i, int start_i, t_data *data);
int		redirect_in(char *in_file, int *error);
int		redirect_out_add(char *out_file, int type, int *error);
void	handle_heredocs(t_token *token, t_data *data);
void	generate_heredoc_name(char *buffer, int size);

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
void	modify_env(t_data *data, char *env_name, char *new_content, int is_plus);
char	**realloc_env(char **env, char *content);
void	sort_env(t_env_list *env);
int		is_good_export_name(char *str);
void	print_export(char **envp);

char	**expand_wildcards(const char *token);
void	free_strs(char **strs);

#endif