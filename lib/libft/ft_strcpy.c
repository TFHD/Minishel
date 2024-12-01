/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:17:14 by albernar          #+#    #+#             */
/*   Updated: 2024/11/24 00:18:06 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*tmp_dest;

	tmp_dest = dest;
	while (*src)
		*tmp_dest++ = *src++;
	*tmp_dest = 0;
	return (dest);
}
