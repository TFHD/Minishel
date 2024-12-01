/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:32:30 by albernar          #+#    #+#             */
/*   Updated: 2024/11/28 19:09:53 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "../lib/libft/libft.h"
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
}						t_token_type;

typedef enum e_logical_operator
{
	LOGICAL_NONE,
	LOGICAL_AND,
	LOGICAL_OR
}						t_logical_operator;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

// Token List
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_token);
void			free_tokens(t_token *head);

// Token Parser Utils
t_token_type	determine_token_type(t_token *last_token);
void			skip_whitespaces(const char *input, int *index);
int				get_operator_type(const char *input,
					t_token_type *type);

// Token Args
char			*extract_arg(const char *input, int *index);

// Token Parser
t_token			*tokenize_input(const char *input);

// Token Error
int				validate_token(t_token *token);

#endif