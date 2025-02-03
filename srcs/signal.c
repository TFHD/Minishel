/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:48:23 by albernar          #+#    #+#             */
/*   Updated: 2025/02/03 01:18:52 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received = 0;

void	accurate_signal(int status, t_data *data)
{
	if (WIFEXITED(status))
	{
		data->exit_code = WEXITSTATUS(status);
		return ;
	}
	else if (WIFSIGNALED(status))
	{
		data->exit_code = 128 + WTERMSIG(status);
		if (data->exit_code == 130)
			ft_dprintf(2, "\n");
		else if (status == 3)
			ft_dprintf(2, "Quit\n");
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
