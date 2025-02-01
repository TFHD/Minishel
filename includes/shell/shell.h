/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 03:33:29 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 20:49:26 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "../../libft/includes/libft.h"
# include "../../srcs/leak_protector/leak_protector.h"
# include <stdlib.h>
# include <stdio.h>

# define LIGHT_BLUE "\e[38;2;135;206;250m"
# define RESET_COLOR "\e[0m"
# define BLACK_TEXT_WHITE_BG "\e[38;2;0;0;0;48;2;255;255;255m"
# define WHITE_TEXT_BLACK_BG "\e[38;2;255;255;255;48;2;0;0;0m"

typedef struct s_data	t_data;
typedef struct s_env_list
{
	void				*content;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}						t_env_list;
// ENV
t_env_list	*create_env_node(void *content);
void		add_env_node(t_env_list **head, t_env_list *new_node);
void		free_env_list(t_env_list *head);
t_env_list	*copy_env(char **envp);

// PROMPT
char		*get_prompt(t_data *data, int interactive);
int			print_header(char *type);
char		*build_prompt_with_home(const char *cwd, const char *home);
char		*build_prompt_without_home(const char *cwd);

#endif