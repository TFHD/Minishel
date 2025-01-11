/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 03:17:47 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/14 23:49:46 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
		free(env[i++]);
	free(env);
}

int is_bad_args(char *str)
{
    while (*str)
    {
        if (!ft_isalpha(*str) && !ft_isdigit(*str) && *str != '_'
            && *str != '=')
            return (1);
        str++;
    }
    return (0);
}

int unset(t_command *cmd, t_data **data)
{
    char    **env;
    int     i;
    int     bad_args;

    if (!cmd->cmds_args[1])
        return (0);
    i = 1;
    bad_args = 0;
    while (cmd->cmds_args[i])
    {
        if (is_bad_args(cmd->cmds_args[i]) && !bad_args)
        {
               write(2, "unset: ", 7);
               write(2, cmd->cmds_args[i], ft_strlen(cmd->cmds_args[i]));
               write(2, ": invalid parameter name\n", 25);
               bad_args = 1; 
        }
        else
        {
            env = env_list_to_char((*data)->env, cmd->cmds_args[i]);
            free_env_list((*data)->env);
            (*data)->env = copy_env(env);
            free_env(env);
        }
        i++;
    }
    i = 0;
    if (bad_args)
        return (1);
    return (0);
}