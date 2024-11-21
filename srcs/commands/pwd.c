/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 01:05:13 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/21 01:52:21 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(int nb_args)
{
	char	cwd[256];

	if (nb_args != 1)
	{
		exit_error(FORMAT_ERR);
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}
