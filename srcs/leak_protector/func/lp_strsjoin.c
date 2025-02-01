/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lp_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:00:38 by albernar          #+#    #+#             */
/*   Updated: 2025/01/31 03:34:14 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../leak_protector.h"
#include "../../../libft/includes/libft.h"

static int	lp_strslen(int strs_count, va_list strs)
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

static void	lp_strsfree(int free_flag, int strs_count, va_list strs)
{
	va_list	strs_copy;
	char	*current_str;
	int		i;

	i = -1;
	va_copy(strs_copy, strs);
	while (++i < strs_count)
	{
		current_str = va_arg(strs, char *);
		if (free_flag & (1 << (strs_count - 1 - i)) && current_str != NULL)
			lp_free(current_str);
	}
	va_end(strs_copy);
}

char	*lp_strsjoin(int free_flag, int strs_count, ...)
{
	va_list	strs;
	int		i;
	char	*result;
	char	*current_str;

	va_start(strs, strs_count);
	result = lp_alloc(sizeof(char), (lp_strslen(strs_count, strs) + 1));
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
		}
	}
	va_start(strs, strs_count);
	lp_strsfree(free_flag, strs_count, strs);
	va_end(strs);
	return (result);
}
