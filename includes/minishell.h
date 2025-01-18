/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:10:43 by albernar          #+#    #+#             */
/*   Updated: 2025/01/16 17:26:35 by sabartho         ###   ########.fr       */
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
	int			pipe[2];
	int			pipe_nb;
}		t_data;

void	extends(char **sub_string, char quote, char quote_after, t_data *data);
void	exec(t_ast *ast, t_data **data);
char	*get_env(t_env_list *env_list, char *env_name);
void	parsing_quote(t_token **token, t_data *data);
void	pre_parsing(t_data **data);
void	signal_handler(int signal);
void	signal2(int signal);
char	*set_path(char *paths, char **path, char *file_name, int i);
void	not_command(char **path);
int		is_builtins(t_data *data, t_command *cmd);

char	**env_list_to_char(t_env_list *head, char *remove);
void	no_option(t_command *cmd);
int		pwd(t_command *cmd);
int		env(t_command *cmd, t_data *data);
int		echo(t_command *cmd);
int		redirect(t_command *cmd);
int		ft_exit(t_command *cmd);
int		cd(t_command *cmd, t_data *data);
void	set_env(t_env_list *env_list, char *env_name, char *new);
int		unset(t_command *cmd, t_data **data);
int		redirect(t_command *cmd);
int		close_dup(int save_stdout);
int		export(t_data *data, t_command *cmd);
int		get_index_env(char **env, char *search);

#endif
