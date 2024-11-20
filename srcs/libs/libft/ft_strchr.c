/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 05:58:03 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/08 06:08:29 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
