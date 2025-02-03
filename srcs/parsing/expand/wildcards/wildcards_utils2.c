/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:48:14 by albernar          #+#    #+#             */
/*   Updated: 2025/02/03 10:41:50 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	free_current_list(char **current_list, char **start_paths)
{
	int	z;

	if (current_list == start_paths || !current_list)
		return ;
	z = -1;
	while (current_list[++z])
		lp_free(current_list[z]);
	lp_free(current_list);
}

char	**create_empty_result(void)
{
	char	**empty;

	empty = lp_alloc(sizeof(char *), 1);
	*empty = NULL;
	return (empty);
}

char	**create_initial_start(int is_absolute)
{
	char	**start;

	start = lp_alloc(sizeof(char *), 2);
	if (is_absolute)
		start[0] = lp_strdup("/");
	else
		start[0] = lp_strdup(".");
	start[1] = NULL;
	return (start);
}

void	handle_single_dot(char **res, int i)
{
	char	*path;
	int		len;
	int		x;

	path = res[i];
	if (path[0] == '.' && path[1] == '/')
	{
		len = ft_strlen(path);
		x = -1;
		while (++x < len - 1)
			path[x] = path[x + 2];
		path[len - 2] = 0;
	}
}

void	handle_empty_path(char **res, int i)
{
	if (!*res[i])
	{
		lp_free(res[i]);
		res[i] = lp_strdup(".");
	}
}
