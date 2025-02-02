/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 04:23:56 by sabartho          #+#    #+#             */
/*   Updated: 2025/02/02 06:53:35 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_home_dir(t_command **cmd, t_data *data, char *dir)
{
	char	*tmp;
	char	*char_tmp;
	int		total_len;

	if (!ft_strncmp(dir, "~/", 2))
	{
		tmp = get_env(data->env, "HOME");
		if (tmp)
		{
			char_tmp = lp_substr(dir, 1, ft_strlen(dir));
			lp_free((*cmd)->cmds_args[1]);
			total_len = ft_strlen(char_tmp) + ft_strlen(tmp) + 1;
			(*cmd)->cmds_args[1] = lp_alloc(sizeof(char), total_len);
			ft_strcpy((*cmd)->cmds_args[1], tmp);
			ft_strcat((*cmd)->cmds_args[1], char_tmp);
			lp_free(char_tmp);
		}
	}
}

int	change_dir(char *dir, t_data **data, int home)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(dir))
	{
		if (pwd)
		{
			set_env((*data)->env, "OLDPWD", pwd);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env((*data)->env, "PWD", pwd);
			free(pwd);
		}
		(void) home;
		return (1);
	}
	return (0);
}

int	set_dir(char *dir, t_data *data, int home)
{
	struct stat	st;

	if (change_dir(dir, &data, home))
		return (0);
	ft_dprintf(2, "minishell: cd: %s", dir);
	if (stat(dir, &st) == -1)
		ft_dprintf(2, ": No such file or directory\n");
	else if (!(st.st_mode & S_IXUSR))
		ft_dprintf(2, ": Permission denied\n");
	else
		ft_dprintf(2, ": Not a directory\n");
	if (home)
		lp_free(dir);
	return (1);
}

int	back_dir(char *dir, t_data **data)
{
	char	*tmp;

	if (!ft_strcmp(dir, "-"))
	{
		tmp = get_env((*data)->env, "OLDPWD");
		if (tmp)
			set_dir(tmp, *data, 0);
		else
		{
			ft_dprintf(2, "joyshell: cd : OLDPWD not set\n");
			return (1);
		}
		tmp = get_env((*data)->env, "PWD");
		if (tmp)
			ft_printf("%s\n", tmp);
		return (0);
	}
	return (set_dir(dir, *data, 0));
}

int	cd(t_command *cmd, t_data *data)
{
	char	*home;
	int		i;

	i = 0;
	while (cmd->cmds_args[i + 1])
		i++;
	if (i > 1)
	{
		ft_dprintf(2, "joyshell: cd: too many arguments\n");
		return (1);
	}
	if (i == 0 || !ft_strcmp(cmd->cmds_args[1], "~")
		|| !ft_strcmp(cmd->cmds_args[1], "--"))
	{
		home = get_env(data->env, "HOME");
		if (!home)
		{
			ft_dprintf(2, "joyshell: cd: HOME not set\n");
			return (1);
		}
		return (set_dir(home, data, 1));
	}
	add_home_dir(&cmd, data, cmd->cmds_args[1]);
	return (back_dir(cmd->cmds_args[1], &data));
}
