/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/12 17:46:07 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include "minishell.h"

static int init_shell(t_shell *sh, char **envp)
{
	char *shlvl_str;
	char *new_shlvl_str;
	int shlvl;

	sh->env = env_init(envp);
	if (!sh->env)
		return (-1);
	sh->global_status = 0;
	shlvl_str = env_get(sh->env, "SHLVL");
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	new_shlvl_str = ft_itoa(shlvl);
	if (!new_shlvl_str)
		return (-1);
	env_set(sh->env, "SHLVL", new_shlvl_str);
	free(new_shlvl_str);
	return (0);
}

void cleanup_shell(t_env_var *env)
{
	t_env_var *tmp;

	if (env)
	{
		while (env)
		{
			tmp = env;
			env = env->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	char *input;
	t_token *tokens;
	t_cmd *cmd;
	t_shell sh;

	(void)argc;
	(void)argv;
	if (init_shell(&sh, envp) != 0)
	{
		ft_putendl_fd("minishell: failed to initialize", STDERR_FILENO);
		return (1);
	}
	setup_signals_interactive();
	sh.curr_line = 1;
	while (sh.global_status != -200)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break;
		}
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		add_history(input);
		if (input)
			tokens = tokenize(&sh, input);
		if (tokens)
		{
			cmd = parse_cmd(tokens);
			setup_signals_execution();
			sh.global_status = exec_command(&sh, cmd);
			setup_signals_interactive();
			ft_free_cmd_list(cmd);
		}
		sh.curr_line++;
	}
	cleanup_shell(sh.env);
	return (0);
}
