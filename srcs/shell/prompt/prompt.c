/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:40:57 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 03:15:04 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	print_header(char *type)
{
	ft_printf("%s                 █▓            \e[0m\n", type);
	ft_printf("%s                 ▓▓░░          \e[0m\n", type);
	ft_printf("%s   ▓             █░░▒▒         \e[0m\n", type);
	ft_printf("%s   ▒▒██       ▓▓██░░▒░         \e[0m\n", type);
	ft_printf("%s   ▓▒▓▒▓███▓▒░░▒▒▒▓▓▒░▒        \e[0m\n", type);
	ft_printf("%s    ░▒▓▒███▒░░░░░░░▓███▓       \e[0m\n", type);
	ft_printf("%s    ▒▓▒▓██▓░░░░░░▓▒░░░▒██      \e[0m\n", type);
	ft_printf("%s     ▒████▓█▓▒▒░░░░░░░░░▓█     \e[0m", type);
	ft_printf("        %sJoyShell\e[0m\n", LIGHT_BLUE);
	ft_printf("%s     ▓█▓▒░▒▒▓▒█▓██░░░░░▒█      \e[0m", type);
	ft_printf("           %sby sabartho\e[0m\n", LIGHT_BLUE);
	ft_printf("%s      ▓▓░░░▒▓▒▒▓▓███░░░░░▓     \e[0m", type);
	ft_printf("         %sand albernar\e[0m\n", LIGHT_BLUE);
	ft_printf("%s      ▓▓▒▒░▓▓▒▓▓▓▒▓▓▒░░░░▒     \e[0m\n", type);
	ft_printf("%s      ▓▓▓▒▒▒██▓▓▓▓▓▒░░░░▒▓     \e[0m\n", type);
	ft_printf("%s      ▓███▓▓▓▓█▓▓▒▒░░░░░░▒     \e[0m\n", type);
	ft_printf("%s      ▓█████▓▒▒▒▒░░░░░░░▒▓     \e[0m\n", type);
	ft_printf("%s       █████▒▒▒▒░░░░░░░▒▓▓     \e[0m\n", type);
	ft_printf("%s        ███████▒░░░░░░░▒▓█▒    \e[0m\n\n\n", type);
	return (0);
}

char	*get_prompt(int interactive)
{
	char	*result;
	char	cwd[4096];
	char	*home;

	if (!interactive)
		return (NULL);
	getcwd(cwd, sizeof(cwd));
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		result = build_prompt_with_home(cwd, home);
	else
		result = build_prompt_without_home(cwd);
	return (result);
}
