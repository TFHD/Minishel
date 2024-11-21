/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 01:30:44 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/21 01:55:27 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ls(char **args, int nb_args)
{
	struct dirent	*d;
	DIR				*dh;

	if (nb_args == 1)
		dh = opendir(".");
	else
		dh = opendir(args[1]);
	while ((d = readdir(dh)) != NULL)
	{
		if (ft_strchr(d->d_name, '.'))
			printf("\e[35m%s  \e[0m", d->d_name);
		else
			printf("\e[34m%s  \e[0m", d->d_name);
	}
	printf("\n");
}
