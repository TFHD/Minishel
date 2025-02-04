/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:47:40 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 10:17:59 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

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
	res = apply_pattern_segments(start, segs, -1);
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

void	sort_wildcards(char **stack_content, int start, int end)
{
	int	pivot;

	if (start < end)
	{
		pivot = partition(stack_content, start, end);
		sort_wildcards(stack_content, start, pivot - 1);
		sort_wildcards(stack_content, pivot + 1, end);
	}
}

void	expand_with_wildcards(char **sub_string)
{
	char	**expand_wc;
	char	*sub_cpy;
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sub_cpy = lp_strdup(*sub_string);
	expand_wc = expand_wildcards(sub_cpy);
	while (expand_wc[j])
		j++;
	sort_wildcards(expand_wc, 0, j - 1);
	if (expand_wc[0])
		res = lp_strdup(expand_wc[0]);
	i++;
	while (expand_wc && expand_wc[i])
		res = lp_strsjoin(0, 3, res, " ", expand_wc[i++]);
	lp_free(*sub_string);
	*sub_string = 0;
	*sub_string = lp_strdup(res);
	lp_free(res);
	lp_free(sub_cpy);
}
