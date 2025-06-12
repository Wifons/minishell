/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:26:24 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/11 22:53:38 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_quote(char *str)
{
	int i;
	int	single_quote;
	int	double_quote;
	
	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote % 2 == 0)
			single_quote++;
		if (str[i] == '\"' && single_quote % 2 == 0)
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (1);
	return (0);
}
int verif_operator_utils(t_shell *shell, t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	while (tmp)
	{
		if (tmp->type == L_REDIRECT || tmp->type == HEREDOC )
			if (ft_strncmp(tmp->value, "<", 2) != 0 && ft_strncmp(tmp->value, "<<", 3) != 0)
				return (syntax_error(shell, tmp->value)); 
		if (tmp->type == R_REDIRECT || tmp->type == APP_REDIRECT )
			if (ft_strncmp(tmp->value, ">", 2) != 0 && ft_strncmp(tmp->value, ">>", 3) != 0)
				return (syntax_error(shell, tmp->value));  
		if (tmp->type == PIPE)
			if (ft_strncmp(tmp->value, "|", 2) != 0)
				return (syntax_error(shell, tmp->value));
		tmp = tmp->next;
	}
	return (0);
}

int verif_other_tokens(t_shell *shell, t_token *tokens)
{
	t_token *tmp;
		
	tmp = tokens;
	while (tmp)
	{
		if (tmp && (tmp->type == PIPE || tmp->type == L_REDIRECT || tmp->type == R_REDIRECT
		|| tmp->type == HEREDOC || tmp->type == APP_REDIRECT))
		{
			if (!tmp->next)
				return (syntax_error(shell, "newline"));
			if ((ft_strncmp(tmp->value, "<", 2) == 0  && (tmp->next->type != L_REDIRECT && tmp->next->type != WORD)))
				return (syntax_error(shell, "newline"));
			if (tmp->next->type != WORD)
				return (syntax_error(shell, tmp->next->value));	   
		}
		tmp = tmp->next;
	}
	return (0);
}

int verif_first_token(t_shell *shell, t_token *tokens)
{
	t_token *tmp;
		
	tmp = tokens;
	if (tmp && (tmp->type == PIPE))
	{
		return (syntax_error(shell, tmp->value));
	}
	return (0);
}

int parsing(t_shell *shell, t_token *tokens)
{
	if (!tokens)
		return (1);
	if (verif_first_token(shell, tokens))
	{
		ft_clean(tokens);
		return (1);
	}
	else if  (verif_other_tokens(shell, tokens))
	{
		ft_clean(tokens);
		return (1);
	}
	else if  (verif_operator_utils(shell, tokens))
	{
		ft_clean(tokens);
		return (1);
	}
	verif_heredoc(tokens);
	if (tokens->type == HEREDOC)
	{
		ft_clean(tokens);
		return (1);
	}
	return (0);
}

int verif_input(t_shell *shell, char *str)
{
	int i;

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

int syntax_error(t_shell *shell, const char *value)
{
	printf("minishell: syntax error near unexpected token `%s'\n", value);
	shell->global_status = 2;
	return (1);
}
