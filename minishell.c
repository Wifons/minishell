/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/12 13:49:26 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_shell(t_shell *sh, char **envp)
{
	sh->env = env_init(envp);
	if (!sh->env)
		return (-1);
	sh->global_status = 0;
	//env refresh
	return (0);
}

void	cleanup_shell(t_env_var *env)
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmd;
	t_shell	sh;
	
	(void)argc;
	(void)argv;
	if (init_shell(&sh, envp) != 0)
	{
		ft_putendl_fd("minishell: failed to initialize", STDERR_FILENO);
		return (1);
	}
	while (sh.global_status !=  -200)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		add_history(input);
		if (input)
			tokens = tokenize(&sh, input);
		if (tokens)
		{
			cmd = parse_cmd(tokens, &sh);
			if (cmd)
				sh.global_status =  exec_command(&sh, cmd);
			ft_free_cmd_list(cmd);
		}
	}
	cleanup_shell(sh.env);
	return (0);
}
