/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:15:57 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 07:19:01 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"
# include <sys/stat.h>

void	exec(t_ast *ast, t_data *data, int pipes);
void	exec_order(t_ast *ast, t_data *data);
char	*set_path(char *paths, char **path, char *file_name, int i);
void	not_command(char **path, t_data *data);
int		cmd_exist(char **path_command, t_data *data, t_command *cmd);
char	*get_executable_file(char *file_name, int i, int start_i, t_data *data);
void	not_command2(char **path, t_data *data, struct stat st);
void	rebuilt_command(t_ast *ast, t_data *data);
void	do_pipe(t_ast *ast, t_data *data, int is_pipe);
void	waitall(t_data *data);
void	child_pipe_finish(t_ast *ast, t_data *data);

#endif