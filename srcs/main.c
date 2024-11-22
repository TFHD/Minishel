/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:13:21 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/22 23:36:37 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char *line, char **args, char *prompt_line)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
	if (line)
		free(line);
	if (prompt_line)
		free(prompt_line);
}

void	reset_prompt(int sig)
{
	(void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

char	*get_prompt_line(char *line, char cwd[256])
{
	char	*join;

	join = ft_strsjoin(0, 3, line, cwd, "\e[0m$ ");
	return (join);
}

void	on_prompt(char **envp, char *prompt_line)
{
	char	**args;
	char	cwd[256];
	char	*line;

	line = readline(prompt_line);
	while (line != NULL)
	{
		args = NULL;
		if (!parse(&args, line))
			envp = function_manager(args, envp, line);
		free_all(line, args, prompt_line);
		getcwd(cwd, sizeof(cwd));
		prompt_line = get_prompt_line(PROMPT_LINE, cwd);
		line = readline(prompt_line);
	}
	//free_all(0, envp, 0);
	free(prompt_line);
}

int	main(int ac, char **av, char **envp)
{
	char	cwd[256];

	(void)ac;
	(void)av;
	getcwd(cwd, sizeof(cwd));

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTRAP, SIG_IGN);
	signal(SIGINT, reset_prompt);
	on_prompt(envp, get_prompt_line(PROMPT_LINE, cwd));
	printf("exit\n");
	return (0);
}
