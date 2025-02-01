/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_protector.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 05:33:14 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 00:38:07 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAK_PROTECTOR_H
# define LEAK_PROTECTOR_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_lp_list
{
	void				*content;
	struct s_lp_list	*next;
}	t_lp_list;

// LeakProtector list
t_lp_list	*lp_lstnew(void *content);
t_lp_list	*lp_lstadd(t_lp_list **head, t_lp_list *new_node);
void		lp_lstdelone(t_lp_list **head, void *content);
void		lp_lstclear(t_lp_list **head);

// LeakProtector func
void		*lp_alloc(size_t nmemb, size_t size);
void		lp_free(void *ptr);
void		lp_freeall(void);

// Func using LeakProtector
char		*lp_strdup(const char *src);
char		*lp_strsjoin(int free_flag, int strs_count, ...);
char		*lp_substr(char const *s, unsigned int start, size_t len);

#endif