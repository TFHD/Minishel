/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:40:57 by albernar          #+#    #+#             */
/*   Updated: 2024/12/14 23:05:31 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	print_header(char *type)
{
	printf("%s                 █▓            \e[0m\n", type);
	printf("%s                 ▓▓░░          \e[0m\n", type);
	printf("%s   ▓             █░░▒▒         \e[0m\n", type);
	printf("%s   ▒▒██       ▓▓██░░▒░         \e[0m\n", type);
	printf("%s   ▓▒▓▒▓███▓▒░░▒▒▒▓▓▒░▒        \e[0m\n", type);
	printf("%s    ░▒▓▒███▒░░░░░░░▓███▓       \e[0m\n", type);
	printf("%s    ▒▓▒▓██▓░░░░░░▓▒░░░▒██      \e[0m\n", type);
	printf("%s     ▒████▓█▓▒▒░░░░░░░░░▓█     \e[0m", type);
	printf("        %sJoyShell\e[0m\n", LIGHT_BLUE);
	printf("%s     ▓█▓▒░▒▒▓▒█▓██░░░░░▒█      \e[0m", type);
	printf("           %sby sabartho\e[0m\n", LIGHT_BLUE);
	printf("%s      ▓▓░░░▒▓▒▒▓▓███░░░░░▓     \e[0m", type);
	printf("         %sand albernar\e[0m\n", LIGHT_BLUE);
	printf("%s      ▓▓▒▒░▓▓▒▓▓▓▒▓▓▒░░░░▒     \e[0m\n", type);
	printf("%s      ▓▓▓▒▒▒██▓▓▓▓▓▒░░░░▒▓     \e[0m\n", type);
	printf("%s      ▓███▓▓▓▓█▓▓▒▒░░░░░░▒     \e[0m\n", type);
	printf("%s      ▓█████▓▒▒▒▒░░░░░░░▒▓     \e[0m\n", type);
	printf("%s       █████▒▒▒▒░░░░░░░▒▓▓     \e[0m\n", type);
	printf("%s        ███████▒░░░░░░░▒▓█▒    \e[0m\n\n\n", type);
	return (0);
}

char	*get_prompt(void)
{
	char	*result;
	char	cwd[4096];
	char	*home;

	getcwd(cwd, sizeof(cwd));
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		result = build_prompt_with_home(cwd, home);
	else
		result = build_prompt_without_home(cwd);
	return (result);
}
