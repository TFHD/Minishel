/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:05:05 by albernar          #+#    #+#             */
/*   Updated: 2025/01/30 07:25:43 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex_bonus.h"
#include "token.h"

int	g_recieved = 0;

void	signal2(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		g_recieved = 130;
	}
	if (signal == SIGQUIT)
	{
		printf("\n");
		g_recieved = 131;
	}
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_recieved = 130;
	}
}

const char	*get_token_type_name(t_token_type type)
{
	static const char	*token_type_names[] = {
		"TOKEN_COMMAND",
		"TOKEN_ARGUMENT",
		"TOKEN_PIPE",
		"TOKEN_LOGICAL_AND",
		"TOKEN_LOGICAL_OR",
		"TOKEN_SUBSHELL_OPEN",
		"TOKEN_SUBSHELL_CLOSE",
		"TOKEN_REDIRECT_IN",
		"TOKEN_REDIRECT_OUT",
		"TOKEN_APPEND_OUT",
		"TOKEN_HEREDOC",
		"TOKEN_END"
	};

	if (type >= 0 && type <= TOKEN_END)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void	print_tokens(t_token *head)
{
	t_token	*current;
	int		index;

	index = 0;
	if (!head)
	{
		printf("No tokens to display.\n");
		return ;
	}
	current = head;
	while (current)
	{
		printf("Token %d: Type = \e[31m%s\e[0m, Value = %s\n",
			index++,
			get_token_type_name(current->type),
			current->value
			);
		current = current->next;
	}
}

static void	__print_node(t_ast *ast, char *x)
{
	static const char		*token_redir[4] = {"<", ">", ">>", "<<"};
	static char				**token = NULL;
	static t_redirection	*red = NULL;

	if (ast && ast->type == TOKEN_PIPE)
		printf("%s%s\n", x, "|");
	else if (ast && ast->type == TOKEN_LOGICAL_AND)
		printf("%s%s\n", x, "&&");
	else if (ast && ast->type == TOKEN_LOGICAL_OR)
		printf("%s%s\n", x, "||");
	else
	{
		if (ast->cmd)
			token = ast->cmd->cmds_args;
		if (ast->cmd && ast->cmd->redirection)
			red = ast->cmd->redirection;
		printf("%s", x);
		while (token && *token)
			printf("{\e[31m%s\e[0m} ", *token++);
		printf("\n");
		printf("%s", x);
		while (red)
		{
			printf("[\e[33m%s\e[0m] {\e[31m%s\e[0m} ", token_redir[red->type - TOKEN_REDIRECT_IN],
				red->redirect);
			red = red->next;
		}
		printf("\n");
	}
}

void	handle_heredocs(t_token *token, t_data **data)
{
	t_token	*token_tmp;
	int		find;

	token_tmp = token;
	find = 0;
	while (token->type != TOKEN_END)
	{
		if (token->type == TOKEN_HEREDOC && (token->next->type != TOKEN_END && token->next->type == TOKEN_ARGUMENT))
		{
			clean_redir((*data)->red_in, -1, -1);
			(*data)->red_in = heredocs(token->next->value, *data);
			find = 1;
		}
		token = token->next;
	}
	if (find)
		get_next_line(-1);
	token = token_tmp;
	clean_redir((*data)->red_in, -1, -1);
	(*data)->red_in = -1;
}

void	__print_tree(t_ast *ast, int tab)
{
	char	*t;

	if (!ast)
		return ;
	__print_tree(ast->left, tab + 8);
	t = calloc(tab + 1, 1);
	if (t)
		memset(t, ' ', tab);
	__print_node(ast, t);
	free(t);
	__print_tree(ast->right, tab + 8);
}

/*
	TODO
	rl_outstream = stderr;
	fprintf();
	IF PIPE IN AST -> LEFT OR RIGHT NOT PIPE NOR CMD == SUBSHELL
*/

void	unlink_all_fds(t_data **data)
{
	int	temp;

	temp = (*data)->fds;
	while(--(*data)->fds >= 0)
		unlink((*data)->fds_here_docs[(*data)->fds]);
	(*data)->fds = temp;
}

void	init_data(t_data **data, char **envp)
{
	int		shlvl;
	int		is_overflow;
	char	*old_shlvl;
	char	new_shlvl[11];

	(*data)->env = copy_env(envp);
	(*data)->token = 0;
	(*data)->exit_code = 0;
	(*data)->red_in = -1;
	(*data)->red_out = -1;
	(*data)->red_app = -1;
	(*data)->pipes[0] = -2;
	(*data)->pipes[1] = -2;
	(*data)->fds = 0;
	(*data)->in_fd = 0;
	old_shlvl = get_env((*data)->env, "SHLVL");
	if (old_shlvl)
	{
		shlvl = ft_atoi(old_shlvl, &is_overflow);
		set_env((*data)->env, "SHLVL", ft_itoa_b(shlvl + 1, new_shlvl));
	}
}

void	_print_data_values(t_data *data)
{
	data->red_in = -1;
	data->red_app = -1;
	data->red_out = -1;
	printf("\n");
	printf("red_in : \e[32m%d\e[0m\n", data->red_in);
	printf("red out : \e[32m%d\e[0m\n", data->red_out);
	printf("red append : \e[32m%d\e[0m\n", data->red_app);
	printf("fds : \e[32m%d\e[0m\n", data->fds);
	printf("in_fd : \e[32m%d\e[0m\n", data->in_fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*cpy_tokens;
	char		*input;
	char		*prompt;
	t_data		*data;

	(void) argc;
	(void) argv;
	//print_header(BLACK_TEXT_WHITE_BG);
	data = lp_alloc(sizeof(t_data), 1);
	init_data(&data, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = get_prompt();
		input = readline(prompt);
		if (g_recieved)
		{
			data->exit_code = g_recieved;
			g_recieved = 0;
		}
		add_history(input);
		if (!input)
			break ;
		lp_free(prompt);
		data->token = tokenize_input(input);
		if (data->token)
			handle_heredocs(data->token, &data);
		if (data->token && data->token->type != TOKEN_END)
		{
			if (validate_token(data->token))
			{
				cpy_tokens = data->token;
				data->ast = create_ast(&data->token);
				print_tokens(cpy_tokens);
				printf("\n-----------------------------\n\n");
				__print_tree(data->ast, 0);
				printf("\n-----------------------------\n\n");
				exec(data->ast, &data, 0);
				free_ast(data->ast);
				free_tokens(cpy_tokens);
			}
			else 
				data->exit_code = 2;
		}
		if (data->fds != 0)
			unlink_all_fds(&data);
		free(input);
		data->in_fd = 0;
	//	_print_data_values(data);
	}
	if (!input)
		lp_free(prompt);
	rl_clear_history();
	free_env_list(data->env);
	printf("exit\n");
}
