/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:40:15 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/09 11:47:46 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_str(char c, char *result, int i)
{
	*(result + i) = c;
}

static void	ft_putnbr(int c, char *result, int i)
{
	if (c == -2147483648)
	{
		put_str('-', result, 0);
		put_str('2', result, 1);
		ft_putnbr(147483648, result, i);
	}
	else if (c < 0)
	{
		put_str('-', result, 0);
		ft_putnbr(-c, result, i);
	}
	else
	{
		if (c >= 10)
			ft_putnbr(c / 10, result, i - 1);
		put_str('0' + c % 10, result, i);
	}
}

char	*ft_itoa(int n)
{
	int		temp_n;
	int		size;
	char	*result;

	temp_n = n;
	size = 1;
	while (temp_n >= 10 || temp_n <= -10)
	{
		temp_n /= 10;
		size++;
	}
	if (n < 0)
		size ++;
	result = malloc(sizeof(char) * size + 1);
	if (!result)
		return (0);
	if (n == 0)
		*result = '0';
	else
		ft_putnbr(n, result, size - 1);
	*(result + size) = '\0';
	return (result);
}
