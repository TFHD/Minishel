/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:24:54 by sabartho          #+#    #+#             */
/*   Updated: 2024/10/10 10:24:55 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new;
	void	*new2;

	if (!f || !del || !f)
		return (0);
	new_list = 0;
	while (lst)
	{
		new = 0;
		new2 = f(lst->content);
		if (new2)
			new = ft_lstnew(new2);
		if (!new)
		{
			del(new2);
			ft_lstclear(&new_list, del);
			return (0);
		}
		ft_lstadd_back(&new_list, new);
		lst = lst->next;
	}
	return (new_list);
}
