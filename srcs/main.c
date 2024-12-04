/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:05:05 by albernar          #+#    #+#             */
/*   Updated: 2024/12/04 15:18:01 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("Token %d: Type = %s, Value = %s\n",
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
			printf("{%s} ", *token++);
		printf("\n");
		printf("%s", x);
		while (red)
		{
			printf("[%s] {%s} ", token_redir[red->type - TOKEN_REDIRECT_IN],
				red->redirect);
			red = red->next;
		}
		printf("\n");
	}
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

int	main(int argc, char **argv, char **envp)
{
	t_ast		*ast;
	t_env_list	*env_list;
	t_token		*tokens;
	t_token		*cpy_tokens;
	char		*input;
	char		*prompt;

	(void) argc;
	(void) argv;
	env_list = copy_env(envp);
	print_header();
	while (1)
	{
		prompt = get_prompt();
		input = readline(prompt);
		add_history(input);
		if (!input)
			break ;
		lp_free(prompt);
		tokens = tokenize_input(input);
		cpy_tokens = tokens;
		parsing_quote(&tokens);
		//expand_tokens(&tokens, env_list);
		ast = create_ast(&tokens);
		print_tokens(cpy_tokens);
		printf("\n-----------------------------\n\n");
		__print_tree(ast, 0);
		free_ast(ast);
		free_tokens(cpy_tokens);
		free(input);
	}
	if (!input)
		lp_free(prompt);
	free_env_list(env_list);
	rl_clear_history();
}
