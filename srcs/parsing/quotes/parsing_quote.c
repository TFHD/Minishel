/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:59:23 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/09 20:12:00 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_text_inside_quote(t_token *token, char quote, int *i, t_data *data)
{
	char	*sub_string;
	int		start_i;

	(*i)++;
	start_i = *i;
	while (token->value[*i] != quote)
		(*i)++;
	sub_string = ft_substr(token->value, start_i, *i - start_i);
	extends(&sub_string, quote, token->value[*i], data);
	(*i)++;
	return (sub_string);
}

char	*get_text_outside_quote(t_token *token, int *i, t_data *data)
{
	char	*sub_string;
	int		start_i;

	start_i = *i;
	while (token->value[*i] && token->value[*i] != '\"'
		&& token->value[*i] != '\'')
		(*i)++;
	sub_string = ft_substr(token->value, start_i, *i - start_i);
	extends(&sub_string, '\"', token->value[*i], data);
	return (sub_string);
}

void	parsing_quote(t_token **token, t_data *data)
{
	char	quote;
	char	*new_str;
	char	*sub_str;
	t_token	*token_tmp;
	int		i;

	i = 0;
	new_str = 0;
	token_tmp = *token;
	while ((*token)->value)
	{
		while (i < (int)ft_strlen((*token)->value))
		{
			quote = (*token)->value[i];
			if (quote == '\"' || quote == '\'')
				sub_str = get_text_inside_quote(*token, quote, &i, data);
			else
				sub_str = get_text_outside_quote(*token, &i, data);
			new_str = ft_strjoin(new_str, sub_str, 1, 1);
		}
		i = 0;
		lp_free((*token)->value);
		(*token)->value = lp_strdup(new_str);
		free(new_str);
		new_str = 0;
		*token = (*token)->next;
	}
	*token = token_tmp;
}
