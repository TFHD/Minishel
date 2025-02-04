/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 07:14:54 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 07:45:50 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include "minishell.h"

char	*get_env(t_env_list *env_list, char *env_name);
char	*get_envp(t_data *data, char *str);
char	**env_list_to_char(t_env_list *head, char *remove);
void	set_env(t_env_list *env_list, char *env_name, char *new);
void	modify_env(t_data *data, char *env_name, char *new_content);
char	**realloc_env(char **env, char *content);
void	sort_env(t_env_list *env);

#endif