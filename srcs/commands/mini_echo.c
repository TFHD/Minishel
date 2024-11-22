/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:31:55 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 23:43:20 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_echo(char **args, int nb_args)
{
	int	i;

	i = 1;
	if (nb_args == 1)
	{
		printf("\n");
		return ;
	}
	while (i < nb_args)
		printf("%s ", args[i++]);
	printf("\n");
}
