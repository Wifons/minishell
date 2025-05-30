/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:24:42 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/28 00:11:30 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_arg(t_cmd *cmd, char *value)
{
	int		i;
	int		j;
	char	**args;
		
	i = 0;
	if (cmd->arguments)
		while (cmd->arguments[i])
			i++;
	args = malloc(sizeof(char *) * (i + 2));
	if (!args)
		return ;
	j = 0;
	while (j < i)
	{
		args[j] = cmd->arguments[j];
		j++;
	}
	args[j] = ft_strdup(value);
	// error check a faire
	args[j + 1] = NULL;
	free(cmd->arguments);
	cmd->arguments = args;
}

void	add_l_red(t_cmd *cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	cmd->l_redirect = ft_strdup((*tokens)->value);
}

void	add_r_red(t_cmd *cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	cmd->r_redirect = ft_strdup((*tokens)->value);
}

void	add_app_red(t_cmd *cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	cmd->app_redirect = ft_strdup((*tokens)->value);
}

void	add_heredoc(t_cmd *cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	if (cmd->heredoc_buff)
		free(cmd->heredoc_buff);
	cmd->heredoc_buff = ft_strdup((*tokens)->value);
}
