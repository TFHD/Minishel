/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:35:33 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 08:15:31 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H
# include "minishell.h"

// Utils
void	handle_empty_path(char **res, int i);
void	handle_single_dot(char **res, int i);
char	**create_initial_start(int is_absolute);
char	**create_empty_result(void);
void	free_current_list(char **current_list, char **start_paths);
int		is_hidden(const char *filename);
void	free_args(char **args);
void	copy_and_append(char **dest, char **src, int count, char *element);
int		match_pattern(const char *filename, const char *pattern);
char	*join_path(const char *dir, const char *name);

// Segments
char	**traverse_one_segment(const char *current_dir, const char *segment);
void	handle_empty_segment(char ***new_list, int *new_count, char *path);
void	handle_non_empty_segment(char ***new_list,
			int *new_count, char *path, char *segment);

// Pattern
char	**apply_pattern_segments(char **start_paths, char **segments, int i);
char	**split_pattern_on_slash(const char *pattern);

char	**expand_wildcards(const char *token);
void	expand_with_wildcards(char **sub_string);
void	sort_wilcrads(char **expand_wc);

#endif
