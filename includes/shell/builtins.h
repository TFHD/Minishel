/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:12:50 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 07:16:16 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int		is_builtins(t_data *data, t_command *cmd);
int		pwd(t_data *data, t_command *cmd);
int		env(t_command *cmd, t_data *data);
int		echo(t_command *cmd);
int		ft_exit(t_command *cmd, t_data *data);
int		cd(t_command *cmd, t_data *data);
int		unset(t_command *cmd, t_data **data);
int		export(t_data **data, t_command *cmd);
int		is_good_export_name(char *str);
void	print_export(char **envp);
void	no_option(t_command *cmd);

#endif