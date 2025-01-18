/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:50:41 by albernar          #+#    #+#             */
/*   Updated: 2024/11/21 22:40:27 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_datap
{
	int		*tab_pid;
	int		pid_count;
	int		exit_status;
	int		argc;
	char	**argv;
	char	**envp;
}			t_datap;

void		error_message(char *message, char *file, int usage, int *tab);
void		free_strs(char **strs);
void		execute_last_cmd(char *cmd, t_datap *data, int file[2],
				int pipefd[2]);
int			fork_pipe(t_datap *data, int pipefd[2], int file[2], char *cmd);
void		child_process(t_datap *data, int pipefd[2], int file[2], char *cmd);
char		*find_envpath(char *cmd, char **envp);
void		execve_command(char *cmd, t_datap *data, int file[2]);
void		close_files(int fd_count, ...);
void		free_multiple_str(int free_count, ...);
void		pipex(int start, t_datap *data);
void		here_doc(int start, t_datap *data);
void		wait_for_children(t_datap *data, int pid_count);
char		*get_next_line(int fd);
void		here_doc_finish(char *line, char *buf, int pipefd[2], t_datap *data);

#endif
