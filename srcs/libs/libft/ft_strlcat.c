/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:43:27 by sabartho          #+#    #+#             */
/*   Updated: 2024/07/15 11:43:30 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	dest_len;

	if ((!dest || !src) && !size)
		return (0);
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + ft_strlen(src));
	size -= (dest_len + 1);
	while (*src && size-- > 0)
		dest[dest_len++] = *(src++);
	dest[dest_len] = '\0';
	return (dest_len + ft_strlen(src));
}
