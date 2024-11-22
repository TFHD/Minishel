/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:47:50 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 08:54:03 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	function_manager(char **args, char **envp, char *line)
{
	int	nb_args;

	nb_args = 0;
	while (args[nb_args])
		nb_args++;
	if (!strcmp("cd", args[0]))
		change_dir(args[1], nb_args);
	else if (!strcmp("pwd", args[0]))
		get_pwd(nb_args);
	else if (!strcmp("export", args[0]))
		printf("export command\n");
	else if (!strcmp("unset", args[0]))
		printf("unset command\n");
	else if (!strcmp("env", args[0]))
		print_envp(envp, nb_args);
	else if (!strcmp("echo", args[0]))
		printf("echo command\n");
	else if (!strcmp("exit", args[0]))
		ft_exit(args, line, nb_args);
	/*else
		Integration execve*/
}
