/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipexsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:08:35 by albernar          #+#    #+#             */
/*   Updated: 2024/11/15 23:59:00 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_find_sep(char *str, char sep)
{
	while (*str && *str != sep)
		str++;
	return (str);
}

static int	find_words(char *str, char charset, char **saveptr)
{
	char	*start;
	int		count;

	count = 0;
	while (*str)
	{
		while (*str && charset && ft_find_sep(str, charset) == str)
			str++;
		count += (*str != 0);
		start = str;
		str = ft_find_sep(start, charset);
		if (!saveptr || !(*start))
			continue ;
		*(saveptr + count - 1) = ft_substr(start, 0, str - start);
		if (!*(saveptr + count - 1))
			break ;
	}
	return (count);
}

static void	free_split(char **strs)
{
	char	**start;

	start = strs;
	while (*strs)
		free(*strs++);
	free(start);
}

static char	*ft_remove_quotes(char *str)
{
	char	*new_str;
	char	*ptr;
	int		len;

	len = 0;
	ptr = str;
	while (*ptr)
	{
		if (*ptr != '"' && *ptr != '\'')
			len++;
		ptr++;
	}
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	ptr = new_str;
	while (*str)
	{
		if (*str != '"' && *str != '\'')
			*ptr++ = *str;
		str++;
	}
	*ptr = 0;
	return (new_str);
}

char	**ft_pipexsplit(char const *s, char c)
{
	char	*cleaned_s;
	char	**result;
	int		size;

	if (!s)
		return (NULL);
	cleaned_s = ft_remove_quotes((char *)s);
	if (!cleaned_s)
		return (NULL);
	size = find_words(cleaned_s, c, 0);
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
	{
		free(cleaned_s);
		return (NULL);
	}
	*(result + size) = NULL;
	if (find_words(cleaned_s, c, result) == size)
	{
		free(cleaned_s);
		return (result);
	}
	free(cleaned_s);
	free_split(result);
	return (NULL);
}
