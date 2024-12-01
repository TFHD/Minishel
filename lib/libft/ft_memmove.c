/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:19:12 by albernar          #+#    #+#             */
/*   Updated: 2024/10/08 00:57:53 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*tmp_dest;
	const unsigned char	*tmp_src;

	if ((!dest && !src) || (!dest || !src))
		return (NULL);
	tmp_dest = dest;
	tmp_src = src;
	if (tmp_dest < tmp_src)
		ft_memcpy(dest, src, n);
	else
	{
		tmp_dest += n;
		tmp_src += n;
		while (n--)
			*(--tmp_dest) = *(--tmp_src);
	}
	return (dest);
}
