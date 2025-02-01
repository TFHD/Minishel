/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_protector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 05:33:33 by albernar          #+#    #+#             */
/*   Updated: 2024/12/09 19:49:51 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leak_protector.h"
#include <stdint.h>
#include <stdio.h>

static void	*lp_memset(void *ptr, int value, size_t num)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)ptr;
	while (num--)
		*byte_ptr++ = (unsigned char)value;
	return (ptr);
}

static void	lp_mem(int act, void *ptr)
{
	static t_lp_list	*memory = NULL;
	t_lp_list			*node;

	if (act == 0)
	{
		node = lp_lstnew(ptr);
		if (!memory)
			memory = node;
		else
			memory = lp_lstadd(&memory, node);
	}
	else if (act == 1)
		lp_lstdelone(&memory, ptr);
	else if (act == 2)
		lp_lstclear(&memory);
}

void	*lp_alloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (__builtin_expect(!nmemb || !size, 0))
		ptr = malloc(0);
	else if (__builtin_expect((nmemb * size / size) != nmemb, 0))
		return (NULL);
	else
		ptr = malloc(nmemb * size);
	if (__builtin_expect(!ptr, 0))
		exit(1);
	lp_memset(ptr, 0, (nmemb * size));
	lp_mem(0, ptr);
	return (ptr);
}

void	lp_free(void *ptr)
{
	if (__builtin_expect(!ptr, 0))
		return ;
	lp_mem(1, ptr);
}

__attribute__((destructor))
void	lp_freeall(void)
{
	lp_mem(2, NULL);
}
