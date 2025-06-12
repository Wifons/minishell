/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 01:13:10 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/13 00:12:32 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_parse(t_cmd **head_cmd, t_token *tokens, t_shell *shell)
{
	ft_free_cmd_list(*head_cmd);
	ft_free_token_list(tokens);
	shell->global_status = 1;
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

int	handle_pipe(t_parse_cmd *parse)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		ft_free_cmd_list(*(parse->head_cmd));
		ft_free_token_list(parse->tokens);
		return (0);
	}
	init_cmd(new_cmd);
	new_cmd->previous_pipe = 1;
	(*parse->cmd)->next_pipe = 1;
	append_cmd(parse->head_cmd, new_cmd);
	(*parse->cmd) = new_cmd;
	(*parse->tmp) = (*parse->tmp)->next;
	return (1);
}

int	handle_token(t_parse_cmd *parse)
{
	if ((*parse->tmp)->type == WORD)
		add_arg((*parse->cmd), (*parse->tmp)->value);
	else if ((*parse->tmp)->type == L_REDIRECT)
	{
		add_l_red((*parse->cmd), parse->tmp);
		if (!check_file_readable(((*parse->cmd))->l_redirect))
			return (error_parse(parse->head_cmd, parse->tokens, parse->shell));
	}
	else if ((*parse->tmp)->type == R_REDIRECT)
	{
		add_r_red((*parse->cmd), parse->tmp);
		// if (!check_file_writable(((*parse->cmd))->r_redirect))
		// 	return (error_parse(parse->head_cmd, parse->tokens, parse->shell));
	}
	else if ((*parse->tmp)->type == APP_REDIRECT)
		add_app_red((*parse->cmd), parse->tmp);
	else if ((*parse->tmp)->type == HEREDOC)
	{
		add_heredoc((*parse->cmd), parse->tmp);
	}
	return (1);
}
t_cmd	*ft_free_parse_cmd(t_parse_cmd *parse, t_cmd *result)
{
	free(parse->cmd);
	free(parse->head_cmd);
	free(parse->tmp);
	if (result)
		return (result);
	else
		return (NULL);
}

t_cmd	*parse_cmd(t_token *tokens, t_shell *shell)
{
	t_parse_cmd	parse;
	t_cmd	*result;
	
	result = NULL;
	if (!init_parse_struct(&parse, tokens, shell))
		return (NULL);
	while (*(parse.tmp))
	{
		if (((*parse.tmp)->type) == PIPE)
		{
			if (!handle_pipe(&parse))
				return (ft_free_parse_cmd(&parse, result));
			continue ;
		}
		if (!handle_token(&parse))
			return (ft_free_parse_cmd(&parse, result));
		*(parse.tmp) = (*(parse.tmp))->next;
	}
	ft_free_token_list(tokens);
	result = *(parse.head_cmd);
	return (ft_free_parse_cmd(&parse, result));
}
/*
t_cmd	*parse_cmd(t_token *tokens, t_shell *shell)
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
}*/
