/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:21:54 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/08 11:29:49 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_letter(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if ((int)set[i] == (int)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	end;

	if (!s1 || !set)
		return (0);
	i = 0;
	end = ft_strlen(s1) - 1;
	while (check_letter(s1[i], set))
		i++;
	while (check_letter(s1[end], set))
		end--;
	return (ft_substr(s1, i, end - i + 1));
}
