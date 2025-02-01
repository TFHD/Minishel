/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 03:40:57 by albernar          #+#    #+#             */
/*   Updated: 2025/02/01 21:06:40 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_prompt(t_data *data, int interactive)
{
	char	*result;
	char	cwd[4096];
	char	*home;
	char	*pwd;

	if (!interactive)
		return (NULL);
	pwd = get_env(data->env, "PWD");
	if ((pwd && !data->pwd) || (pwd && ft_strcmp(pwd, data->pwd) != 0))
		data->pwd = lp_strdup(pwd);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		if (pwd)
			result = build_prompt_without_home(pwd);
		else
			result = lp_strdup(".$ ");
		return (result);
	}
	home = get_env(data->env, "HOME");
	if (home && !ft_strncmp(cwd, home, ft_strlen(home)))
		result = build_prompt_with_home(cwd, home);
	else
		result = build_prompt_without_home(cwd);
	return (result);
}
