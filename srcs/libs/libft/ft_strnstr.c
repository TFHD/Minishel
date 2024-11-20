/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:46:25 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/08 07:37:27 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!str || !to_find) && !n)
		return (0);
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0] && (i + j) < n)
		{
			while (str[i + j] == to_find[j] && (i + j) < n)
			{
				if (to_find[j + 1] == '\0')
					return ((char *)str + i);
				j++;
			}
		}
		i++;
		j = 0;
	}
	return ((char *)0);
}
