/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:31:35 by albernar          #+#    #+#             */
/*   Updated: 2024/10/08 00:59:19 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmenb, size_t size)
{
	void	*ptr;

	if (nmenb && (nmenb * size) / nmenb != size)
		return (NULL);
	ptr = malloc(nmenb * size);
	if (!ptr)
		return (NULL);
	if (size == 0)
		return (ptr);
	ft_bzero(ptr, nmenb * size);
	return (ptr);
}
