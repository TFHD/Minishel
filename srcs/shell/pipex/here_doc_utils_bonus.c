/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:40:09 by albernar          #+#    #+#             */
/*   Updated: 2024/11/22 00:54:45 by albernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_finish(char *line, char *buf, int pipefd[2], t_datap *data)
{
	if (!line)
	{
		write(2, "Error: here_doc delimited by end-of-file (wanted `", 50);
		write(2, data->argv[2], ft_strlen(data->argv[2]));
		write(2, "')\n", 3);
	}
	if (buf)
		write(pipefd[1], buf, ft_strlen(buf));
	close(pipefd[1]);
	free_multiple_str(2, buf, data->tab_pid);
	get_next_line(-1);
}
