/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:48:23 by albernar          #+#    #+#             */
/*   Updated: 2025/01/31 03:43:54 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received = 0;

void	accurate_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		g_received = 130;
	}
	if (signal == SIGQUIT)
	{
		ft_printf("\n");
		g_received = 131;
	}
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_received = 130;
	}
}
