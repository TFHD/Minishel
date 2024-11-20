/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:47:50 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/20 20:53:21 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	function_manager(char **args)
{
	if (!strcmp("cd", args[0]))
		printf("cd command\n");
	else if (!strcmp("pwd", args[0]))
		printf("pwd command\n");
	else if (!strcmp("export", args[0]))
		printf("export command\n");
	else if (!strcmp("unset", args[0]))
		printf("unset command\n");
	else if (!strcmp("env", args[0]))
		printf("env command\n");
	else if (!strcmp("echo", args[0]))
		printf("echo command\n");
	else
		printf("invalid command !\n");
}
