/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:13:21 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/21 02:26:09 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**args;
	char	cwd[256];

	(void)ac;
	(void)av;
	getcwd(cwd, sizeof(cwd));
	printf("\e[1;32mMinishell@%s\e[0m$", cwd);
	line = readline(" ");
	while (line != NULL)
	{
		parse(&args, line);
		if (args)
		{
			function_manager(args, envp, line);
			free_args(args);
		}
		free(line);
		getcwd(cwd, sizeof(cwd));
		printf("\e[1;32mMinishell@%s\e[0m$", cwd);
		line = readline(" ");
	}
	printf("exit\n");
	return (0);
}
