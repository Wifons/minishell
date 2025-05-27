/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/27 20:00:23 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_shell(t_shell *shell, char **envp)
{
	shell->last_exit_status = 0;
	if (init_env(shell, envp) == GENERAL_ERROR)
		return (GENERAL_ERROR);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmd;
	t_shell shell;
	
	(void)argc;
	(void)argv;
	if (init_shell(&shell, envp) == GENERAL_ERROR)
		return (GENERAL_ERROR);
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
		//add_history(input);
		tokens = tokenize(input);
		if (tokens)
		{
			cmd = parse_cmd(tokens);
			exec_command(&shell, cmd);
		}
		//ft_free_cmd_lst(cmd);
		/*if (tokens)
		{
			print_tokens(tokens);
			ft_clean(tokens);
		}*/
	}
	//clean_minishell();
	return (0);
}
