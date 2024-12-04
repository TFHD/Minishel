/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:40:57 by albernar          #+#    #+#             */
/*   Updated: 2024/12/04 15:08:11 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_header(void)
{
	printf("%s                 █▓            \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s                 ▓▓░░          \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s   ▓             █░░▒▒         \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s   ▒▒██       ▓▓██░░▒░         \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s   ▓▒▓▒▓███▓▒░░▒▒▒▓▓▒░▒        \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s    ░▒▓▒███▒░░░░░░░▓███▓       \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s    ▒▓▒▓██▓░░░░░░▓▒░░░▒██      \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s     ▒████▓█▓▒▒░░░░░░░░░▓█     \e[0m", BLACK_TEXT_WHITE_BG);
	printf("        %sJoyShell\e[0m\n", LIGHT_BLUE);
	printf("%s     ▓█▓▒░▒▒▓▒█▓██░░░░░▒█      \e[0m", BLACK_TEXT_WHITE_BG);
	printf("           %sby sabartho\e[0m\n", LIGHT_BLUE);
	printf("%s      ▓▓░░░▒▓▒▒▓▓███░░░░░▓     \e[0m", BLACK_TEXT_WHITE_BG);
	printf("         %sand albernar\e[0m\n", LIGHT_BLUE);
	printf("%s      ▓▓▒▒░▓▓▒▓▓▓▒▓▓▒░░░░▒     \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s      ▓▓▓▒▒▒██▓▓▓▓▓▒░░░░▒▓     \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s      ▓███▓▓▓▓█▓▓▒▒░░░░░░▒     \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s      ▓█████▓▒▒▒▒░░░░░░░▒▓     \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s       █████▒▒▒▒░░░░░░░▒▓▓     \e[0m\n", BLACK_TEXT_WHITE_BG);
	printf("%s        ███████▒░░░░░░░▒▓█▒    \e[0m\n\n\n", BLACK_TEXT_WHITE_BG);
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
