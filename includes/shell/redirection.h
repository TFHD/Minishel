/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:09:50 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 07:17:52 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H
# include "minishell.h"

int		redirect_in(char *in_file, int *error);
int		redirect_out_add(char *out_file, int type, int *error);
int		handle_heredocs(t_token *token, t_data *data);
void	generate_heredoc_name(char *buffer, int size);
int		redirect(t_ast *ast, t_data *data);
int		heredocs(char *delimiter, t_data *data);
void	clean_redir(int save_in, int save_out, int save_out2);
void	extends_heredocs(char **sub_string, t_data *data);
void	unlink_fd(t_data *data);
int		token_is_before_invalid_token(t_token *token, t_token *bad_token);

#endif