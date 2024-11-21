/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:22:25 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/21 00:55:19 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(char **envp, int nb_args)
{
	if (nb_args != 1)
	{
		exit_error(FORMAT_ERR);
		return ;
	}
	while (*envp)
		printf("%s\n", *(envp++));
}
