/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:32:44 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 07:17:53 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_to_end_quote(char *line, int i)
{
	char	quote;

	quote = *(line + i);
	i++;
	while (*(line + i) != quote)
		i++;
	return (i);
}

int	fill_to_end_quote(char *args, char *line, char quote, int i)
{
	int	j;

	j = 0;
	*(args + j++) = *(line + i++);
	while (*(line + i) != quote)
		*(args + j++) = *(line + i++);
	*(args + j++) = *(line + i++);
	*(args + j) = 0;
	return (i);
}

int	count_quote(char *line)
{
	int	simple_q;
	int	multi_q;

	simple_q = 0;
	multi_q = 0;
	while (*line)
	{
		if (*line == '\'' && multi_q % 2 != 1)
			simple_q++;
		else if (*line == '\"' )
			multi_q++;
		line++;
	}
	if (simple_q % 2 == 1 || multi_q % 2 == 1)
		return (1);
	return (0);
}

//"bonjour" c "moi"
//01234567890123456
