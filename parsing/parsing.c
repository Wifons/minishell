/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:26:24 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:41:22 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_operator_utils(t_shell *shell, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == L_REDIRECT || tmp->type == HEREDOC
			|| tmp->type == R_REDIRECT || tmp->type == APP_REDIRECT)
		{
			if (!tmp->next)
				return (syntax_error(shell, "newline"));
			else if (tmp->next->type != WORD)
				return (syntax_error(shell, tmp->next->value));
		}
		tmp = tmp->next;
	}
	return (0);
}

int	verif_other_tokens(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next)
				return (syntax_error(shell, "newline"));
			if (tmp->next->type == PIPE)
				return (syntax_error(shell, tmp->value));
		}
		tmp = tmp->next;
	}
	return (0);
}

int	verif_first_token(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp && (tmp->type == PIPE))
	{
		return (syntax_error(shell, tmp->value));
	}
	return (0);
}

int	parsing(t_shell *shell, t_token *tokens)
{
	if (!tokens)
		return (1);
	if (verif_first_token(shell, tokens))
	{
		ft_clean(tokens);
		return (1);
	}
	else if (verif_other_tokens(shell, tokens))
	{
		ft_clean(tokens);
		return (1);
	}
	else if (verif_operator_utils(shell, tokens))
	{
		ft_clean(tokens);
		return (1);
	}
	verif_heredoc(shell, tokens);
	if (tokens->type == HEREDOC)
	{
		ft_clean(tokens);
		return (1);
	}
	return (0);
}

int	verif_input(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (1);
	if (str[0] == '!' && !str[1])
	{
		shell->global_status = 1;
		return (1);
	}
	else if (str[0] == ':' && !str[1])
	{
		shell->global_status = 0;
		return (1);
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\n')
	{
		shell->global_status = 0;
		return (1);
	}
	return (0);
}
