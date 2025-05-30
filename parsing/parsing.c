/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:26:24 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/27 23:26:51 by tcassu           ###   ########.fr       */
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
int verif_operator_utils(t_token *token)
{
    t_token *tmp;

    tmp = token;
    
    while (tmp)
    {
        if (tmp->type == L_REDIRECT || tmp->type == HEREDOC )
            if (ft_strncmp(tmp->value, "<", 2) != 0 && ft_strncmp(tmp->value, "<<", 3) != 0)
                return (1);
        if (tmp->type == R_REDIRECT || tmp->type == APP_REDIRECT )
            if (ft_strncmp(tmp->value, ">", 2) != 0 && ft_strncmp(tmp->value, ">>", 3) != 0)
                return (1);
        if (tmp->type == PIPE)
            if (ft_strncmp(tmp->value, "|", 2) != 0)
                return (1);
        tmp = tmp->next;
    }
    return (0);
}

int verif_other_tokens(t_token *tokens)
{
    t_token *tmp;
    
    tmp = tokens;
    while (tmp)
    {
        if (tmp && (tmp->type == PIPE || tmp->type == L_REDIRECT || tmp->type == R_REDIRECT
        || tmp->type == HEREDOC || tmp->type == APP_REDIRECT))
        {
            if (!tmp->next)
            {
                printf("Minishell : syntax error2\n");
                return (1);
            }
            if (tmp->next->type != WORD)
            {
                
                printf("Minishell : syntax error3\n");
                return (1);
            }       
        }
        tmp = tmp->next;
    }
    return (0);
}

int verif_first_token(t_token *tokens)
{
    t_token *tmp;
    
    tmp = tokens;
    if (tmp && (tmp->type == PIPE))
    {
        ft_clean(tokens);
        return (1);
    }
    return (0);
}

int parsing(t_token *tokens)
{
    if (verif_first_token(tokens))
    {
        printf("code 1\n");
        return (1);
    }
    else if  (verif_other_tokens(tokens))
    {
        printf("code 1\n");
        ft_clean(tokens);
        return (1);
    }
    else if  (verif_operator_utils(tokens))
    {
        printf("code 1\n");
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

int verif_input(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (1);
    if (str[0] == '!' && !str[1])
        return (1);
    else if (str[0] == ':' && !str[1])
        return (1);
    else if (str[0] == '\0' && !str[1])
        return (1);
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '\n')
        return (1);
    return (0);
}