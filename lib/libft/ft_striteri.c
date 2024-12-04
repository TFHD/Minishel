/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:57:33 by albernar          #+#    #+#             */
/*   Updated: 2024/11/05 15:29:09 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char	*tmp_s;

	if (!s)
		return ;
	tmp_s = (char *)s - 1;
	while (*++tmp_s)
		f(tmp_s - s, &(*tmp_s));
}
