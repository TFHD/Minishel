/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:41:17 by albernar          #+#    #+#             */
/*   Updated: 2024/12/03 20:02:31 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "../lib/libft/libft.h"
# include "../srcs/leak_protector/leak_protector.h"
# include <stdlib.h>
# include <stdio.h>

# define LIGHT_BLUE "\001\033[38;2;135;206;250m\002"
# define RESET_COLOR "\001\033[0m\002"
# define BLACK_TEXT_WHITE_BG "\033[38;2;0;0;0;48;2;255;255;255m"

typedef struct s_env_list
{
	void				*content;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}					t_env_list;

// ENV
t_env_list	*create_env_node(void *content);
void		add_env_node(t_env_list **head, t_env_list *new_node);
void		free_env_list(t_env_list *head);
t_env_list	*copy_env(char **envp);
char		*get_env(t_env_list *env_list, char *env_name);

// PROMPT
char		*get_prompt(t_env_list *env_list);
void		print_header(void);
char		*build_prompt_with_home(const char *cwd, const char *home);
char		*build_prompt_without_home(const char *cwd);

#endif