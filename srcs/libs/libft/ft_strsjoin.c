/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:42:14 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 00:21:32 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	ft_strslen(int strs_count, va_list strs)
{
	va_list	strs_copy;
	char	*current_str;
	int		total_len;

	total_len = 0;
	va_copy(strs_copy, strs);
	while (strs_count-- > 0)
	{
		current_str = va_arg(strs_copy, char *);
		if (current_str)
			total_len += ft_strlen(current_str);
	}
	va_end(strs_copy);
	return (total_len);
}

char	*ft_strsjoin(int free_flag, int strs_count, ...)
{
	va_list	strs;
	int		i;
	char	*result;
	char	*current_str;

	va_start(strs, strs_count);
	result = malloc(sizeof(char) * (ft_strslen(strs_count, strs) + 1));
	if (result)
	{
		*result = 0;
		i = -1;
		va_start(strs, strs_count);
		while (++i < strs_count)
		{
			current_str = va_arg(strs, char *);
			if (current_str)
				ft_strcat(result, current_str);
			if (free_flag & (1 << (strs_count - 1 - i)) && current_str != NULL)
				free(current_str);
		}
	}
	va_end(strs);
	return (result);
}
