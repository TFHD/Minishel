/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:34:41 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 08:41:20 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **envp)
{
	int		shlvl;
	char	*old_shlvl;
	char	new_shlvl[11];

	data->env = copy_env(envp);
	data->token = 0;
	data->exit_code = 0;
	data->redirects.in = -1;
	data->redirects.out = -1;
	data->redirects.append = -1;
	data->pipefd[0] = -2;
	data->pipefd[1] = -2;
	data->fd = 0;
	data->infile = 0;
	data->pipe_fds = 0;
	data->pwd = NULL;
	old_shlvl = get_env(data->env, "SHLVL");
	if (old_shlvl)
	{
		shlvl = ft_atoi(old_shlvl, NULL);
		ft_itoa_buffer(shlvl + 1, new_shlvl);
		set_env(data->env, "SHLVL", new_shlvl);
	}
}

__attribute__ ((constructor))
void	setup_readline(void)
{
	rl_outstream = stderr;
	if (!isatty(0))
		rl_prep_term_function = 0;
}

/*
*	FOR DEBUG ONLY
*	t_token	*cpy_tokens;
*	cpy_tokens = data->token; (before create_ast)
*/
void	process_token(t_data *data)
{
	if (!handle_heredocs(data->token, data))
	{
		data->ast = create_ast(&data->token);
		exec(data->ast, data, 0);
		waitall(data);
		free_ast(data->ast);
	}
	else
		data->exit_code = 2;
}

int	process_input(char *prompt, t_data *data)
{
	char	*input;

	input = readline(prompt);
	data->input = lp_strdup(input);
	free(input);
	lp_free(prompt);
	if (g_received)
	{
		data->exit_code = g_received;
		g_received = 0;
	}
	if (data->input)
		add_history(data->input);
	if (!data->input)
		return (1);
	data->token = tokenize_input(data->input);
	if (data->token && data->token->type != TOKEN_END)
		process_token(data);
	if (data->fd != 0)
		unlink_fd(data);
	if (data->infile != 0)
		close(data->infile);
	data->infile = 0;
	lp_free(data->input);
	return (0);
}

int	main(
	__attribute__ ((unused)) int argc,
	__attribute__ ((unused)) char **argv,
	char **envp
)
{
	t_data	data;
	char	*prompt;

	init_data(&data, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = get_prompt(&data, isatty(0));
		if (process_input(prompt, &data))
			break ;
		lp_free(data.token);
		data.redirects.in = -1;
		data.redirects.append = -1;
		data.redirects.out = -1;
	}
	rl_clear_history();
	if (isatty(0))
		ft_dprintf(2, "exit\n");
	free_env_list(data.env);
	return (data.exit_code);
}
