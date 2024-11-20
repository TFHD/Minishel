/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:50:01 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/10 05:50:02 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int c, int fd)
{
	if (c == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (c < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-c, fd);
	}
	else
	{
		if (c >= 10)
			ft_putnbr_fd(c / 10, fd);
		ft_putchar_fd('0' + c % 10, fd);
	}
}
