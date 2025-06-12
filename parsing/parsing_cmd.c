/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 01:13:10 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/09 01:13:59 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_parse(t_cmd **head_cmd, t_token *tokens)
{
	ft_free_cmd_list(*head_cmd);
	ft_free_token_list(tokens);
	return (0);
}

int	check_file_readable(const char *filename)
{
	if (access(filename, R_OK) == -1)
	{
		perror(filename);
		return (0);
	}
	return (1);
}

int	check_file_writable(const char *filename)
{
	if (access(filename, W_OK) == -1)
	{
		perror(filename);
		return (0);
	}
	return (1);
}

int	handle_pipe(t_cmd **cmd, t_cmd **head_cmd, t_token **tmp, t_token *tokens)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		ft_free_cmd_list(*head_cmd);
		ft_free_token_list(tokens);
		return (0);
	}
	init_cmd(new_cmd);
	new_cmd->previous_pipe = 1;
	(*cmd)->next_pipe = 1;
	append_cmd(head_cmd, new_cmd);
	*cmd = new_cmd;
	*tmp = (*tmp)->next;
	return (1);
}

int	handle_token(t_cmd **cmd, t_cmd **head_cmd, t_token **tmp, t_token *tokens)
{
	if ((*tmp)->type == WORD)
		add_arg(*cmd, (*tmp)->value);
	else if ((*tmp)->type == L_REDIRECT)
	{
		add_l_red(*cmd, tmp);
		if (!check_file_readable((*cmd)->l_redirect))
			return (error_parse(head_cmd, tokens));
	}
	else if ((*tmp)->type == R_REDIRECT)
	{
		add_r_red(*cmd, tmp);
		if (!check_file_writable((*cmd)->r_redirect))
			return (error_parse(head_cmd, tokens));
	}
	else if ((*tmp)->type == APP_REDIRECT)
		add_app_red(*cmd, tmp);
	else if ((*tmp)->type == HEREDOC)
	{
		add_heredoc(*cmd, tmp);
	}
	return (1);
}

t_cmd	*parse_cmd(t_token *tokens)
{
	t_cmd	*head_cmd;
	t_cmd	*cmd;
	t_token	*tmp;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(cmd);
	head_cmd = cmd;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!handle_pipe(&cmd, &head_cmd, &tmp, tokens))
				return (NULL);
			continue ;
		}
		if (!handle_token(&cmd, &head_cmd, &tmp, tokens))
			return (NULL);
		tmp = tmp->next;
	}
	ft_free_token_list(tokens);
	return (head_cmd);
}
