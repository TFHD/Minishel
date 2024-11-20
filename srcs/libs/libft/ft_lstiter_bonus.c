/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:14:16 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/10 10:23:14 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_tmp;

	if (!lst)
		return ;
	while (lst)
	{
		lst_tmp = lst->next;
		f(lst->content);
		lst = lst_tmp;
	}
}
