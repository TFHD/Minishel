/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:47:40 by albernar          #+#    #+#             */
/*   Updated: 2025/02/03 07:56:50 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static void	process_relative_results(char **res)
{
	int	i;

	i = -1;
	while (res[++i])
	{
		handle_single_dot(res, i);
		handle_empty_path(res, i);
	}
}

static char	**expand_path_pattern(const char *pattern)
{
	char	**segs;
	char	**start;
	char	**res;
	int		is_absolute;

	segs = split_pattern_on_slash(pattern);
	if (!segs)
		return (create_empty_result());
	is_absolute = (pattern[0] == '/');
	start = create_initial_start(is_absolute);
	if (!start)
		return (NULL);
	res = apply_pattern_segments(start, segs);
	free_args(segs);
	if (!res)
		return (NULL);
	if (!is_absolute)
		process_relative_results(res);
	return (res);
}

char	**expand_wildcards(const char *token)
{
	int		i;
	int		has_star;
	char	**expanded;

	if (!token)
		return (NULL);
	has_star = 0;
	i = -1;
	while (token[++i])
		if (token[i] == '*')
			has_star = 1;
	if (has_star)
		expanded = expand_path_pattern(token);
	if (!has_star || !expanded || !expanded[0])
	{
		if (expanded)
			free_args(expanded);
		expanded = lp_alloc(sizeof(char *), 2);
		expanded[0] = lp_strdup(token);
		expanded[1] = NULL;
	}
	return (expanded);
}
