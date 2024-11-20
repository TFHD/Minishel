/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:14:51 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/08 09:20:59 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	unsigned long	len_tot;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	len_tot = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * len_tot + 1);
	if (!join)
		return (0);
	if (s1)
		while (s1[i])
			join[j++] = (char)s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			join[j++] = (char)s2[i++];
	join[j] = '\0';
	return (join);
}
