/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:43:42 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/10 09:43:44 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		lst_tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lst_tmp;
	}
}
