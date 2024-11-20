/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:41:57 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/09 08:42:12 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_before_charset(char const *str, char charset, int i)
{
	int	size;

	size = 0;
	while (str[i] != charset && str[i])
	{
		size++;
		i++;
	}
	return (size);
}

static int	ft_count_words(const char *str, char charset)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str && str[i])
	{
		if (str[i] != charset)
		{
			word++;
			while (str[i] != charset && str[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}

static void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**strs;
	int		size;
	int		j;

	i = 0;
	j = -1;
	strs = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (0);
	while (++j < ft_count_words(s, c))
	{
		while (s[i] == c)
			i++;
		size = ft_size_before_charset(s, c, i);
		strs[j] = ft_substr(s, i, size);
		if (!strs[j])
		{
			ft_free(strs, j);
			return (0);
		}
		i += size;
	}
	strs[j] = 0;
	return (strs);
}
