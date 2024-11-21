/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:26:01 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/21 00:54:36 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char *dir, int nb_args)
{
	int	succes;

	if (nb_args > 2)
	{
		exit_error(FORMAT_ERR);
		return ;
	}
	if (nb_args == 1)
		dir = ft_strdup("/nfs/homes/sabartho/");
	succes = chdir(dir);
	if (succes)
	{
		exit_error(CHDIR_ERR);
		printf("%s\n", dir);
	}
	if (nb_args == 1)
		free(dir);
}
