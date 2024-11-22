/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:30:15 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 08:28:33 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PARSE_ERR "parsing error !\n"
# define FORMAT_ERR "Invalid format error !\n"
# define MALOC_ERR "Malloc error !\n"
# define CHDIR_ERR "cd : no such file or directory: "
# define PROMPT_LINE "\e[1;32mMinishell@"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../srcs/libs/libft/libft.h"

//Parsing functions 

int		parse(char ***args, char *line);
int		go_to_end_quote(char *line, int);
int		fill_to_end_quote(char *args, char *line, char quote, int i);
int		count_quote(char *line);
void	get_env(char **args, int nb_args);

//Error functions

int		exit_error(char *str);

//Commmand functions

void	function_manager(char **args, char **envp, char *line);

void	print_envp(char **envp, int nb_args);
void	change_dir(char *dir, int nb_args);
void	get_pwd(int nb_args);
void	ft_exit(char **args, char *line, int nb_args);
void	ls(char **dir, int nb_args);

#endif
