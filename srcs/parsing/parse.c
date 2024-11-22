/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:24:00 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 06:23:18 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *line, char sep)
{
	int	i;
	int	nb_args;

	i = 0;
	nb_args = 0;
	while (i < (int)ft_strlen(line))
	{
		if (*(line + i) == '\"' || *(line + i) == '\'')
		{
			i = go_to_end_quote(line, i) + 1;
			nb_args++;
		}
		else
		{
			if (((*(line + i) == sep && *(line + i + 1) != sep) && (*(line + i - 1) != '\"' && *(line + i - 1) != '\'')) || *(line + i + 1) == 0)
				nb_args++;
			i++;
		}
	}
	return (nb_args);
}

int	size_arg(char *line)
{
	int	i;

	i = 0;
	while (*(line + i) == ' ')
		line++;
	if (*(line + i) == '\"' || *(line + i) == '\'')
		i = go_to_end_quote(line, i) + 1;
	else
	{
		while (*(line + i) && *(line + i) != ' ')
			i++;
	}
	return (i);
}

int	fill_arg(char *args, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*(line + i) == ' ')
		i++;
	if (*(line + i) == '\"' || *(line + i) == '\'')
		i = fill_to_end_quote(args, line, *(line + i), i);
	else
	{
		while (*(line + i) && *(line + i) != ' ')
			*(args + j++) = *(line + i++);
		*(args + j) = 0;
		i++;
	}
	return (i);
}

int	split_args(char **args, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (int)ft_strlen(line))
	{
		args[j] = malloc(sizeof(char) * (size_arg(line + i) + 1));
		if (!args[j])
		{
			while (j >= 0)
				free(args[j--]);
			free(args);
			return (1);
		}
		i += fill_arg(args[j], line + i);
		j++;
	}
	args[j] = 0;
	return (0);
}

int	parse(char ***args, char *line)
{
	int		nb_args;

	if (count_quote(line))
		return (1);
	nb_args = count_args(line, ' ');
	if (!nb_args)
		return (1);
	*args = malloc(sizeof(char *) * (nb_args + 1));
	if (!*args)
		return (exit_error(PARSE_ERR));
	if (split_args(*args, line))
		return (exit_error(PARSE_ERR));
	//parsing_quote(*args)
	get_env(*args, nb_args);
	return (0);
}
