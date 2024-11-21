/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 01:11:05 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/21 02:28:24 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **args, char *line, int nb_args)
{
	int	i;

	i = 0;
	if (nb_args != 1)
	{
		exit_error(FORMAT_ERR);
		return ;
	}
	while (args[i])
		free(args[i++]);
	free(args);
	free(line);
	exit(EXIT_FAILURE);
}
