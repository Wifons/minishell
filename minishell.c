/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 15:57:14 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int init_shell(t_shell *sh, char **envp)
{
	char *shlvl_str;
	char *new_shlvl_str;
	char	*uid_str;
	int shlvl;

	sh->env = env_init(envp);
	if (!sh->env)
		return (-1);
	sh->global_status = 0;
	sh->should_exit = 0;
	uid_str = ft_itoa(getuid());
	if (uid_str)
	{
		env_set(sh->env, "UID", uid_str);
		free(uid_str);
	}
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

void	cleanup_shell(t_env_var *env)
{
	t_env_var *tmp;

	if (env)
	{
		while (env)
		{
			tmp = env->next;
			free(env->name);
			free(env->value);
			free(env);
			env = tmp;
		}
	}
}

int	main(int argc, char **argv, char **envp)
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
	while (!sh.should_exit)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		if (input)
			tokens = tokenize(&sh, input);
		if (tokens)
		{
			cmd = parse_cmd(tokens, &sh);
			setup_signals_execution();
			if (cmd)
				sh.global_status = exec_command(&sh, cmd);
			setup_signals_interactive();
			ft_free_cmd_list(cmd);
		}
		sh.curr_line++;
	}
	cleanup_shell(sh.env);
	rl_clear_history();
	return (sh.global_status);
}
