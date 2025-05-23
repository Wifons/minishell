/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/23 15:20:59 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmd;
	
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
			execute_command(cmd);
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
