/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:59:23 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/02 05:04:36 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_parsing(t_token **token)
{
	t_token	*token_tmp;
	char	*str;

	token_tmp = *token;
	str = lp_strdup((*token)->value);
	*token = (*token)->next;
	while ((*token)->value)
	{
		str = lp_strsjoin(0b100, 3, str, " ", (*token)->value);
		*token = (*token)->next;
	}
	(*token) = token_tmp;
	free_tokens(*token);
	*token = tokenize_input(str);
	lp_free(str);
}

static char	*get_text_inside_quote(t_token *token,
	char quote, int *i, t_data *data)
{
	char	*sub_string;
	int		start_i;

	(*i)++;
	start_i = *i;
	while (token->value[*i] != quote)
		(*i)++;
	sub_string = lp_substr(token->value, start_i - data->type_parse,
			*i - start_i + (2 * data->type_parse));
	if (data->expand)
		extends(&sub_string, quote, token->value[*i], data);
	(*i)++;
	return (sub_string);
}

static char	*get_text_outside_quote(t_token *token, int *i, t_data *data)
{
	char	*sub_string;
	int		start_i;

	start_i = *i;
	while (token->value[*i] && token->value[*i] != '\"'
		&& token->value[*i] != '\'')
		(*i)++;
	if (token->value[*i] == '\"' && token->value[*i - 1] == '$')
		return (lp_substr(token->value, start_i, *i - start_i - 1));
	sub_string = lp_substr(token->value, start_i, *i - start_i);
	if (data->expand)
		extends(&sub_string, '\"', token->value[*i], data);
	return (sub_string);
}

static void	process_quote(t_token **token, t_data *data)
{
	char	quote;
	char	*new_str;
	char	*sub_str;
	int		i;

	i = 0;
	new_str = 0;
	while (i < (int)ft_strlen((*token)->value))
	{
		quote = (*token)->value[i];
		if ((quote == '\"' || quote == '\''))
			sub_str = get_text_inside_quote(*token, quote, &i, data);
		else
			sub_str = get_text_outside_quote(*token, &i, data);
		new_str = lp_strsjoin(0b11, 2, new_str, sub_str);
	}
	lp_free((*token)->value);
	(*token)->value = lp_strdup(new_str);
	lp_free(new_str);
	new_str = 0;
}

void	parsing_quote(t_token **token, t_data *data, int expand)
{
	t_token	*token_tmp;

	token_tmp = *token;
	data->expand = expand;
	while ((*token)->value)
	{
		if (!ft_strncmp((*token)->value, "&&", 2))
			break ;
		process_quote(token, data);
		*token = (*token)->next;
	}
	*token = token_tmp;
}
