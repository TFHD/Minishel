/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 07:58:54 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/10 08:03:26 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = malloc(sizeof(t_list) * 1);
	if (!new_lst)
		return (0);
	new_lst->content = content;
	new_lst->next = 0;
	return (new_lst);
}
