/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:24:00 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/21 00:51:17 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *line, char sep)
{
	int	nb_args;
	int	i;

	i = 0;
	nb_args = 0;
	while (line[i] == sep)
		i++;
	while (line[i] != 0)
	{
		if ((line[i] == sep && line[i + 1] != sep) || line[i + 1] == 0)
			nb_args++;
		i++;
	}
	return (nb_args);
}

int	size_arg(char *line)
{
	int	i;

	i = 0;
	while (*line == ' ')
		line++;
	while (*line != ' ' && *line != 0)
	{
		i++;
		line++;
	}
	return (i);
}

int	fill_arg(char *args, char *line)
{
	int	i;

	i = 0;
	while (*line == ' ')
	{
		i++;
		line++;
	}
	while (*line != ' ' && *line != 0)
	{
		*args++ = *line++;
		i++;
	}
	*args = 0;
	return (i + 1);
}

int	split_args(char **args, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (int)ft_strlen(line) && line[i] != 0)
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

	nb_args = count_args(line, ' ');
	if (!nb_args)
		return (1);
	*args = malloc(sizeof(char *) * (nb_args + 1));
	if (!*args)
		return (exit_error(PARSE_ERR));
	if (split_args(*args, line))
		return (exit_error(PARSE_ERR));
	return (0);
}
