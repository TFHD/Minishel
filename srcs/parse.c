/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:24:00 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/20 20:01:47 by sabartho         ###   ########.fr       */
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

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

int	split_args(char **args, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(line) && line[i] != 0)
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

char	**parse(char *line)
{
	char	**args;
	int		nb_args;

	nb_args = count_args(line, ' ');
	if (!nb_args)
		return (0);
	args = malloc(sizeof(char *) * (nb_args + 1));
	if (!args)
		return (parsing_error());
	if (split_args(args, line))
		return (parsing_error());
	return (args);
}
