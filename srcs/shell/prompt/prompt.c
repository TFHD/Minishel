/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:40:57 by albernar          #+#    #+#             */
/*   Updated: 2024/12/03 20:02:16 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_header(void)
{
	printf(BLACK_TEXT_WHITE_BG "                 █▓            \n");
	printf("                 ▓▓░░          \n");
	printf("   ▓             █░░▒▒         \n");
	printf("   ▒▒██       ▓▓██░░▒░         \n");
	printf("   ▓▒▓▒▓███▓▒░░▒▒▒▓▓▒░▒        \n");
	printf("    ░▒▓▒███▒░░░░░░░▓███▓       \n");
	printf("    ▒▓▒▓██▓░░░░░░▓▒░░░▒██      \n");
	printf("     ▒████▓█▓▒▒░░░░░░░░░▓█     		" \
		RESET_COLOR LIGHT_BLUE "JoyShell" RESET_COLOR "\n");
	printf(BLACK_TEXT_WHITE_BG "      ▓█▓▒░▒▒▓▒█▓██░░░░░▒█     		" \
		RESET_COLOR LIGHT_BLUE "  by sabartho" RESET_COLOR "\n");
	printf(BLACK_TEXT_WHITE_BG "      ▓▓░░░▒▓▒▒▓▓███░░░░░▓     		" \
		RESET_COLOR LIGHT_BLUE "   and albernar" RESET_COLOR "\n");
	printf(BLACK_TEXT_WHITE_BG "      ▓▓▒▒░▓▓▒▓▓▓▒▓▓▒░░░░▒     \n");
	printf("      ▓▓▓▒▒▒██▓▓▓▓▓▒░░░░▒▓     \n");
	printf("      ▓███▓▓▓▓█▓▓▒▒░░░░░░▒     \n");
	printf("      ▓█████▓▒▒▒▒░░░░░░░▒▓     \n");
	printf("       █████▒▒▒▒░░░░░░░▒▓▓     \n");
	printf("        ███████▒░░░░░░░▒▓█▒    \n\n\n" RESET_COLOR);
}

char	*get_prompt(t_env_list *env_list)
{
	char	*result;
	char	cwd[4096];
	char	*home;

	getcwd(cwd, sizeof(cwd));
	home = get_env(env_list, "HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		result = build_prompt_with_home(cwd, home);
	else
		result = build_prompt_without_home(cwd);
	return (result);
}
