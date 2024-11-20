/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:51:28 by sabartho          #+#    #+#             */
/*   Updated: 2024/07/18 12:51:29 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*ptr_cpy;
	int		size;
	int		i;

	size = 0;
	while (src[size])
		size++;
	i = 0;
	ptr_cpy = malloc(sizeof(char) * size + 1);
	if (ptr_cpy == 0)
		return (0);
	while (i < size)
	{
		ptr_cpy[i] = src[i];
		i++;
	}
	ptr_cpy[i] = '\0';
	return (ptr_cpy);
}
