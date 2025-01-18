/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:50:23 by albernar          #+#    #+#             */
/*   Updated: 2024/11/16 06:47:20 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test(int argc, char **argv, char **envp)
{
	t_datap	data;
	int		cmds_start;

	if (argc < 5)
		error_message(NULL, NULL, 2, NULL);
	cmds_start = 2;
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.tab_pid = NULL;
	data.exit_status = 0;
	data.pid_count = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc(cmds_start + 1, &data);
	else
		pipex(cmds_start, &data);
	return (WEXITSTATUS(data.exit_status));
}
