/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:13:14 by albernar          #+#    #+#             */
/*   Updated: 2025/02/03 08:58:37 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static char	*finish_split_pattern(const char *pattern, int i, int start)
{
	char	*segment;
	int		segment_len;
	int		j;

	segment_len = i - start;
	j = -1;
	segment = lp_alloc(sizeof(char), segment_len + 1);
	while (++j < segment_len)
		segment[j] = pattern[start + j];
	segment[segment_len] = 0;
	return (segment);
}

char	**split_pattern_on_slash(const char *pattern)
{
	char	**segments;
	int		seg_count;
	int		i;
	int		start;
	int		id;

	seg_count = 1;
	i = -1;
	while (pattern[++i])
		if (pattern[i] == '/')
			seg_count++;
	segments = lp_alloc(sizeof(char *), (seg_count + 1));
	id = 0;
	start = 0;
	i = -1;
	while (++i <= (int)ft_strlen(pattern))
	{
		if (pattern[i] == '/' || !pattern[i])
		{
			segments[id++] = finish_split_pattern(pattern, i, start);
			start = i + 1;
		}
	}
	segments[id] = NULL;
	return (segments);
}

char	**apply_pattern_segments(char **start_paths, char **segments)
{
	char	**current_list;
	int		i;
	char	**new_list;
	int		new_count;
	int		pidx;

	if (!start_paths || !segments)
		return (NULL);
	current_list = start_paths;
	i = -1;
	while (segments[++i])
	{
		new_list = NULL;
		new_count = 0;
		pidx = -1;
		while (current_list[++pidx])
		{
			if (ft_strlen(segments[i]) == 0)
				handle_empty_segment(&new_list, &new_count, current_list[pidx]);
			else
				handle_non_empty_segment(&new_list, &new_count,
					current_list[pidx], segments[i]);
		}
		free_current_list(current_list, start_paths);
		current_list = new_list;
	}
	return (current_list);
}
