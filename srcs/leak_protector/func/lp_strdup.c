/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lp_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:33:00 by albernar          #+#    #+#             */
/*   Updated: 2024/11/27 04:35:47 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../leak_protector.h"

char	*lp_strdup(const char *src)
{
	const char	*new_src;
	char		*dest;

	if (!src)
		return (NULL);
	new_src = src;
	while (*new_src)
		new_src++;
	dest = lp_alloc(sizeof(char), (new_src - src + 1));
	if (!dest)
		return (NULL);
	new_src = dest;
	while (*src)
		*dest++ = *src++;
	*dest = 0;
	return ((char *)new_src);
}
