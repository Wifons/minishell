/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/01 15:00:57 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_shell(t_shell *sh, char **envp)
{
	sh->env = env_init(envp);
	if (!sh->env)
		return (-1);
	//env refresh
	return (0);
}

static void	cleanup_shell(t_shell *sh)
{
	if (sh && sh->env)
		env_free(sh->env);
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
	while (1)
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
			tokens = tokenize(input);
		if (tokens)
		{
			cmd = parse_cmd(tokens);
			exec_command(&sh, cmd);
			ft_free_cmd_list(cmd);
		}
	}
	cleanup_shell(&sh);
	return (0);
}
