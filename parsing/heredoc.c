/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:57:51 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/27 21:25:33 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_heredoc(char    *eof_hd)
{
    char    *new_value;
    char    *gnlreturn;

    new_value = "\0";
    gnlreturn = NULL;
    while (1)
    {
        gnlreturn = get_next_line(0);
        if (ft_strncmp(eof_hd, gnlreturn, ft_strlen(eof_hd)) == 0)
            break ;
        new_value = ft_strjoin(new_value, gnlreturn);
    }
    printf("After :%s\n", new_value);
    free(eof_hd);
    return (new_value);
}

int verif_heredoc(t_token *tokens)
{
    t_token *tmp;
    
    tmp = tokens;
    while (tmp)
    {
        if (tmp && (tmp->type == HEREDOC))
        {
            if (!tmp->next)
            {
                printf("Minishell : Syntax error near unexpected token 'newline'\n");
                return (1);
            }
            if (tmp->next->type != WORD)
            {
                
                printf("Minishell : syntax error3\n");
                return (1);
            }
            tmp = tmp->next;
            tmp->value = ft_heredoc(tmp->value); 
            
        }
        tmp = tmp->next;
    }
    return (0);
}