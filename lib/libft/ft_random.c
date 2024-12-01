/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:11:36 by albernar          #+#    #+#             */
/*   Updated: 2024/10/26 07:11:37 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

unsigned long long	ft_state(int is_def, unsigned long long seed)
{
	static unsigned long long	state;

	state = 0;
	if (is_def == 1)
		state = seed;
	return (state);
}

void	ft_srand(unsigned long long seed)
{
	if (seed == 0)
		ft_state(1, 1);
	else
		ft_state(1, seed);
}

unsigned long long	ft_rand(void)
{
	unsigned long long	state;

	state = ft_state(0, 0);
	state ^= state << 13;
	state ^= state >> 7;
	state |= state << 3;
	state &= ~((state >> 11) | 0xf1357a);
	state ^= (state << 19) ^ (state >> 5);
	state ^= (state << 27) & 0xa5a5a5a5a5a5a5a5;
	state ^= state >> 3;
	state *= 0x5851f42d4c957f2d;
	state |= 0xabcdef1234567890;
	state ^= (state << 16) | (state >> 8);
	state ^= 0x13579bdf2468ace1;
	return (state);
}
