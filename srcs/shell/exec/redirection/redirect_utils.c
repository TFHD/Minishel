/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:57:10 by albernar          #+#    #+#             */
/*   Updated: 2025/02/02 22:55:09 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_heredoc_name(char *buffer, int size)
{
	int		i;
	int		fd;
	char	value;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return ;
	buffer[0] = '.';
	read(fd, buffer + 1, size - 2);
	close(fd);
	i = 0;
	while (++i < size - 1)
	{
		if (i % 2 == 1)
		{
			value = buffer[i] & 15;
			buffer[i] = '0' + (value % 10);
		}
		else
		{
			value = buffer[i] & 31;
			buffer[i] = 'a' + (value % 26);
		}
	}
	buffer[size - 1] = 0;
}

void	clean_redir(int save_in, int save_out, int save_out2)
{
	if (save_in > 0)
	{
		dup2(save_in, 0);
		close(save_in);
	}
	if (save_out > 0)
	{
		dup2(save_out, 1);
		close(save_out);
	}
	if (save_out2 > 0)
	{
		dup2(save_out2, 1);
		close(save_out2);
	}
}


void	extends_heredocs(char **sub_string, t_data *data)
{
	int		i;
	char	*env;

	i = -1;
	while (++i < (int)ft_strlen(*sub_string))
	{
		if (*(*sub_string + i) == '$' && (ft_isalnum(*(*sub_string + i + 1))
			|| *(*sub_string + i + 1) == '_'))
		{
			env = get_envp(data, *sub_string + i);
			*sub_string = replace(*sub_string, *sub_string + i, i, data);
			i += ft_strlen(env) - 1;
		}
	}
}

int	token_is_before_invalid_token(t_token *token, t_token *bad_token)
{
	t_token_type	bad_type;
	char			*bad_value;
	if (bad_token == NULL)
		return (1);
	bad_value = bad_token->value;
	bad_type = bad_token->type;
	if (token->type == bad_type && token->value == bad_value)
		return (0);
	return (1);

}
