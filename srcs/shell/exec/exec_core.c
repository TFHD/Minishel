/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 05:54:09 by albernar          #+#    #+#             */
/*   Updated: 2025/02/04 08:38:12 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

char	**prepare_exec_order(t_ast *ast, t_data *data, char **path_command)
{
	int		status;
	pid_t	pid;
	char	**env;

	status = 0;
	env = env_list_to_char(data->env, 0);
	pid = fork();
	if (pid == -1)
		return (NULL);
	else if (pid == 0 && *path_command)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		rl_clear_history();
		execve(*path_command, ast->cmd->cmds_args, env);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, signal_handler);
	}
	if (*path_command)
		accurate_signal(status, data);
	return (env);
}

void	exec_order(t_ast *ast, t_data *data)
{
	int		i;
	char	**env;
	char	*path_command;

	i = 0;
	if (is_builtins(data, ast->cmd))
		return ;
	if (*ast->cmd->cmds_args && !cmd_exist(&path_command, data, ast->cmd))
	{
		env = prepare_exec_order(ast, data, &path_command);
		while (env && env[i])
			lp_free(env[i++]);
		if (env)
			lp_free(env);
		lp_free(path_command);
	}
}

static void	exec_node(t_ast *ast, t_data *data, int pipe)
{
	if (pipe && (*ast->cmd->cmds_args || ast->cmd->redirection))
		do_pipe(ast, data, pipe);
	else
	{
		if (ast->cmd->redirection)
			redirect(ast, data);
		else
		{
			if (*ast->cmd->cmds_args)
				rebuilt_command(ast, data);
			exec_order(ast, data);
		}
	}
}

#ifdef BONUS

void	exec(t_ast *ast, t_data *data, int pipe)
{
	if (!ast)
		return ;
	if (ast->type >= TOKEN_PIPE && ast->type <= TOKEN_LOGICAL_OR)
	{
		if (ast->type == TOKEN_PIPE)
			exec(ast->left, data, pipe + 1);
		else
			exec(ast->left, data, pipe);
	}
	data->redirects.in = -1;
	data->redirects.append = -1;
	data->redirects.out = -1;
	exec_node(ast, data, pipe);
	if ((data->exit_code == 0 && ast->type == TOKEN_LOGICAL_AND)
		|| (data->exit_code != 0 && ast->type == TOKEN_LOGICAL_OR)
		|| (ast->type == TOKEN_PIPE))
	{
		if (ast->type == TOKEN_PIPE
			&& pipe == 0 && ast->right->type == TOKEN_COMMAND)
			exec(ast->right, data, -1);
		else
			exec(ast->right, data, pipe);
	}
}

#else

void	exec(t_ast *ast, t_data *data, int pipe)
{
	if (!ast)
		return ;
	if (ast->type >= TOKEN_PIPE)
	{
		if (ast->type == TOKEN_PIPE)
			exec(ast->left, data, pipe + 1);
		else
			exec(ast->left, data, pipe);
	}
	data->redirects.in = -1;
	data->redirects.append = -1;
	data->redirects.out = -1;
	exec_node(ast, data, pipe);
	if (ast->type == TOKEN_PIPE)
	{
		if (ast->type == TOKEN_PIPE
			&& pipe == 0 && ast->right->type == TOKEN_COMMAND)
			exec(ast->right, data, -1);
		else
			exec(ast->right, data, pipe);
	}
}

#endif
