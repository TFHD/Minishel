/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:30:36 by albernar          #+#    #+#             */
/*   Updated: 2025/01/31 03:35:42 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "../libft/includes/libft.h"
# include "../srcs/leak_protector/leak_protector.h"
# include <stdlib.h>
# include <stdio.h>
# define SYNTAX_ERROR "joyshell: syntax error: "

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_LOGICAL_AND,
	TOKEN_LOGICAL_OR,
	TOKEN_SUBSHELL_OPEN,
	TOKEN_SUBSHELL_CLOSE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC,
	TOKEN_END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_token);
void			free_tokens(t_token *head);

t_token_type	determine_token_type(t_token *last_token);
void			skip_whitespaces(const char *input, int *index);
int				get_operator_type(const char *input,
					t_token_type *type);
char			*extract_arg(const char *input, int *index);

t_token			*tokenize_input(const char *input);
int				validate_token(t_token *token);

#endif