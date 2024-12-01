/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:00:00 by albernar          #+#    #+#             */
/*   Updated: 2024/11/28 14:27:48 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static char	*extract_arg_quotes(const char *input, int *index)
{
	int		i;
	int		start;
	char	*arg;
	char	quote_char;

	i = *index;
	quote_char = input[i];
	i++;
	start = i;
	while (input[i] && input[i] != quote_char)
		i++;
	if (input[i] != quote_char)
	{
		fprintf(stderr, SYNTAX_ERROR"unmatched %c\n", quote_char);
		return (NULL);
	}
	arg = lp_alloc(sizeof(char), (i - start + 3));
	arg[0] = quote_char;
	ft_strncpy(&arg[1], &input[start], i - start);
	arg[i - start + 1] = quote_char;
	arg[i - start + 2] = 0;
	*index = i + 1;
	return (arg);
}

static char	*handle_quoted_part(const char *input, int *index, char *arg)
{
	char	*quoted_part;

	quoted_part = extract_arg_quotes(input, index);
	if (!quoted_part)
		return (NULL);
	if (arg)
		arg = lp_strsjoin(0b11, 2, arg, quoted_part);
	else
		arg = quoted_part;
	return (arg);
}

static char	*handle_non_quoted_part(const char *input, int *index, char *arg)
{
	int		start;
	int		word_len;
	char	*non_quoted_part;

	start = *index;
	while (input[*index] && !ft_iswhitespace(input[*index])
		&& get_operator_type(&input[*index], NULL) == -1
		&& input[*index] != '\'' && input[*index] != '"')
		(*index)++;
	word_len = *index - start;
	non_quoted_part = lp_alloc(sizeof(char), (word_len + 1));
	ft_strncpy(non_quoted_part, &input[start], word_len);
	non_quoted_part[word_len] = 0;
	if (arg)
		arg = lp_strsjoin(0b11, 2, arg, non_quoted_part);
	else
		arg = non_quoted_part;
	return (arg);
}

char	*extract_arg(const char *input, int *index)
{
	char	*arg;

	arg = NULL;
	while (input[*index] && !ft_iswhitespace(input[*index])
		&& get_operator_type(&input[*index], NULL) == -1)
	{
		if (input[*index] == '\'' || input[*index] == '"')
		{
			arg = handle_quoted_part(input, index, arg);
			if (!arg)
				return (NULL);
		}
		else
			arg = handle_non_quoted_part(input, index, arg);
	}
	return (arg);
}
