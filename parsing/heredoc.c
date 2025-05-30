/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:57:51 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/28 00:37:40 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cmp_heredoc(char *eof, char  *returngnl)
{
    size_t  len;

    len = ft_strlen(returngnl);
    if (len > 0 && returngnl[len -1] == '\n')
        returngnl[len - 1] = '\0';
    if (ft_strcmp(eof, returngnl) == 0)
        return (1);
    returngnl[len - 1] = '\n';
    return (0);
}
char    *ft_heredoc(char    *eof_hd)
{
    char    *new_value;
    char    *gnlreturn;
    char    *tmp;
    
    new_value = ft_strdup("\0");
    gnlreturn = NULL;
    while (1)
    {
        write(1, "> ", 2);
        gnlreturn = get_next_line(0);
        if (ft_cmp_heredoc(eof_hd, gnlreturn))
        {
            free(gnlreturn);
            break ;
        }
        tmp = new_value;
        new_value = ft_strjoin(new_value, gnlreturn);
        free(gnlreturn);
        if (new_value)
            free(tmp);
    }
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
            tmp->value = remove_quotes(tmp->value);
            tmp->value = ft_heredoc(tmp->value);
            
        }
        tmp = tmp->next;
    }
    return (0);
}