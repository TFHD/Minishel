/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:06:38 by albernar          #+#    #+#             */
/*   Updated: 2025/02/03 08:58:48 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	is_hidden(const char *filename)
{
	if (!filename)
		return (0);
	return (*filename == '.');
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		lp_free(args[i++]);
	lp_free(args);
}

void	copy_and_append(char **dest, char **src, int count, char *element)
{
	int	nn;

	nn = -1;
	while (++nn < count)
		dest[nn] = src[nn];
	dest[count] = element;
	dest[count + 1] = NULL;
}

int	match_pattern(const char *filename, const char *pattern)
{
	int	i;

	if (!*pattern)
		return (!*filename);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (1);
		i = -1;
		while (filename[++i])
			if (match_pattern(&filename[i], pattern))
				return (1);
		return (match_pattern("", pattern));
	}
	else
	{
		if (*filename == *pattern)
			return (match_pattern(filename + 1, pattern + 1));
		return (0);
	}
}

char	*join_path(const char *dir, const char *name)
{
	const int	len[2] = {ft_strlen(dir), ft_strlen(name)};
	char		*res;
	int			need_slash;
	int			id;
	int			i;

	if (!dir || !name)
		return (NULL);
	need_slash = 1;
	if (len[0] == 1 && *dir == '/')
		need_slash = 0;
	res = lp_alloc(sizeof(char), (len[0] + len[1] + need_slash + 1));
	id = 0;
	i = -1;
	while (++i < len[0])
		res[id++] = dir[i];
	if (need_slash)
		res[id++] = '/';
	i = -1;
	while (++i < len[1])
		res[id++] = name[i];
	res[id] = 0;
	return (res);
}
