/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_segments_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:24:57 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 10:17:59 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

static void	add_to_results(char ***results, char *fullpath, int *count)
{
	char	**tmp;
	int		i;

	tmp = lp_alloc(sizeof(char *), (*count + 2));
	i = -1;
	while (++i < *count)
		tmp[i] = (*results)[i];
	tmp[*count] = fullpath;
	(*count)++;
	tmp[*count] = NULL;
	lp_free(*results);
	*results = tmp;
}

static char	**fill_one_segment(char **results, const char *current_dir,
		const char *segment, DIR *d)
{
	struct dirent	*entry;
	char			*full_path;
	int				count;

	count = 0;
	entry = readdir(d);
	while (entry)
	{
		full_path = entry->d_name;
		if (!is_hidden(segment) && is_hidden(full_path))
			entry = readdir(d);
		if (!is_hidden(segment) && is_hidden(full_path))
			continue ;
		if (match_pattern(entry->d_name, segment))
		{
			full_path = join_path(current_dir, full_path);
			if (!full_path)
				entry = readdir(d);
			if (!full_path)
				continue ;
			add_to_results(&results, full_path, &count);
		}
		entry = readdir(d);
	}
	return (results);
}

char	**traverse_one_segment(const char *current_dir, const char *segment)
{
	DIR		*d;
	char	**res;

	d = opendir(current_dir);
	if (!d)
	{
		res = lp_alloc(sizeof(char *), 1);
		*res = NULL;
		return (res);
	}
	res = fill_one_segment(NULL, current_dir, segment, d);
	closedir(d);
	if (!res)
	{
		res = lp_alloc(sizeof(char *), 1);
		*res = NULL;
	}
	return (res);
}

void	handle_empty_segment(char ***new_list, int *new_count, char *path)
{
	char	**tmp;
	char	*dup;
	int		len;
	int		x;

	tmp = lp_alloc(sizeof(char *), (*new_count + 2));
	len = ft_strlen(path);
	dup = lp_alloc(sizeof(char), len + 1);
	x = -1;
	while (++x < len)
		dup[x] = path[x];
	dup[len] = 0;
	copy_and_append(tmp, *new_list, *new_count, dup);
	lp_free(*new_list);
	*new_list = tmp;
	(*new_count)++;
}

void	handle_non_empty_segment(char ***new_list,
	int *new_count, char *path, char *segment)
{
	char	**matches;
	char	**tmp;
	int		c;
	int		mm;

	matches = traverse_one_segment(path, segment);
	c = 0;
	while (matches && matches[c])
		c++;
	mm = -1;
	while (++mm < c)
	{
		tmp = lp_alloc(sizeof(char *), (*new_count + 2));
		copy_and_append(tmp, *new_list, *new_count, matches[mm]);
		lp_free(*new_list);
		*new_list = tmp;
		(*new_count)++;
	}
	mm = c;
	while (matches[mm])
		lp_free(matches[mm++]);
	lp_free(matches);
}
