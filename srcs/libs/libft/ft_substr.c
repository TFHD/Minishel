/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:45:41 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/08 09:09:41 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*ptr;
	unsigned int		i;
	unsigned int		len_sub;

	if (!s)
		return (0);
	len_sub = ft_strlen(s);
	if (len_sub <= start)
		return (ft_strdup(""));
	if (len_sub - start < len)
		len = len_sub - start;
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		ptr[i] = (char)s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
