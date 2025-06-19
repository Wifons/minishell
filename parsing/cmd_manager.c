/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 23:45:22 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 17:04:41 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_token_list(t_token *tokens)
{
	t_token	*tmp;

	if (tokens)
	{
		while (tokens)
		{
			tmp = tokens;
			tokens = tokens->next;
			free(tmp->value);
			free(tmp);
		}
	}
}

void	ft_operator_free(t_cmd *cmd)
{
	t_redir_ordered	*tmp;

	if (cmd->app_redirect)
		free(cmd->app_redirect);
	if (cmd->l_redirect)
		free(cmd->l_redirect);
	if (cmd->r_redirect)
		free(cmd->r_redirect);
	if (cmd->heredoc_buff)
		free(cmd->heredoc_buff);
	while (cmd->redir_list)
	{
		tmp = cmd->redir_list;
		cmd->redir_list = cmd->redir_list->next;
		free(tmp->filename);
		free(tmp);
	}
}

void	ft_free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		i = 0;
		tmp = cmd;
		cmd = cmd->next;
		if (tmp)
		{
			if (tmp->arguments)
			{
				while (tmp->arguments[i])
				{
					free(tmp->arguments[i]);
					i++;
				}
			}
			ft_operator_free(tmp);
			free(tmp->arguments);
		}
		free(tmp);
	}
}

void	init_cmd(t_cmd *cmd)
{
	cmd->arguments = NULL;
	cmd->l_redirect = NULL;
	cmd->r_redirect = NULL;
	cmd->app_redirect = NULL;
	cmd->heredoc_buff = NULL;
	cmd->redir_list = NULL;
	cmd->previous_pipe = 0;
	cmd->next_pipe = 0;
	cmd->next = NULL;
}

void	append_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!head || !new_cmd)
		return ;
	if (*head == NULL)
	{
		*head = new_cmd;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}
