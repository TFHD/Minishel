/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:05:24 by sabartho          #+#    #+#             */
/*   Updated: 2025/01/11 14:09:00 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi_exit(char *str, int *is_overflow, unsigned long long result)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	*is_overflow = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && ++i)
	{
		if ((((result * 10 + (*str - '0') > LLONG_MAX) && sign == 1)
				|| ((result * 10 + (*str - '0') - 1 >= LLONG_MAX)
					&& sign == -1))
			&& i >= 19)
			*is_overflow = 1;
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	check_args(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str != '\f' && *str != '\t' && *str != '\r'
			&& *str != '\v' && *str != ' ')
		{
			if (*str < '0' || *str > '9')
				return (1);
		}
		str++;
	}
	return (0);
}

int	error_in_exit(t_command *cmd, int is_overflow)
{
	int	bad_args;
	int	i;

	i = 0;
	while (cmd->cmds_args[i])
		i++;
	bad_args = check_args(cmd->cmds_args[1]);
	if (is_overflow || bad_args)
	{
		write(2, "joyshell: exit: ", 16);
		write(2, cmd->cmds_args[1], ft_strlen(cmd->cmds_args[1]));
		write (2, ": numeric argument required\n", 28);
		return (2);
	}
	else if (i > 2 && !is_overflow && !bad_args)
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	return (0);
}

int	ft_exit(t_command *cmd)
{
	int			is_overflow;
	long long	code;
	int			exit_error;

	if (!cmd->cmds_args[1])
	{
		exit(0);
		return (0);
	}
	code = ft_atoi_exit(cmd->cmds_args[1], &is_overflow, 0);
	exit_error = error_in_exit(cmd, is_overflow);
	if (exit_error)
	{
		if (exit_error == 2)
			exit (exit_error);
		return (exit_error);
	}
	else
	{
		exit(code % 256);
		return (code % 256);
	}
}
