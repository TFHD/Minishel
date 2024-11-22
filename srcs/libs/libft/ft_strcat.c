/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:06:58 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 00:15:40 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dst, char *src)
{
	char	*tmp_dst;

	tmp_dst = dst;
	while (*tmp_dst)
		tmp_dst++;
	while (*src)
		*tmp_dst++ = *src++;
	*tmp_dst = 0;
	return (dst);
}
