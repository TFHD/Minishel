/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lp_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:37:32 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 00:44:15 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/includes/libft.h"
#include "../leak_protector.h"

char	*lp_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp_dest;
	char	*dest;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (!len)
		start = 0;
	if (ft_strlen(s) < len + start)
		len = ft_strlen(s + start);
	dest = lp_alloc(sizeof(char), (len + 1));
	s += start;
	tmp_dest = dest;
	while (*s && len--)
		*tmp_dest++ = *s++;
	*tmp_dest = 0;
	return (dest);
}
