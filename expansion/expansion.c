/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:05:37 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:10:46 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    expansion(t_token *tokens)
{
    t_token *tmp;
    
    tmp = tokens;
    while(tmp)
    {
        if (tmp->type == WORD)
            tmp->value = expand_variable_dq(tmp->value);
        tmp = tmp->next;
    }
}

char    *expand_and_delete(char    *value, char *variable, char *var_env)
{
    int i;
    int j;
    char    *tmp;
    char    *new_value;
    
    j = 0;
    i = 0;
    while (value[i] != '$' && value[i] && check_in_quote(value, i) != 1)
        i++;
    j = i + 1 + ft_strlen(variable);
    
    tmp = ft_substr(value, 0, i);
    if (var_env)
        new_value = ft_strjoin(tmp, var_env);
    else
        new_value = ft_strdup(tmp);

    free(tmp);
    tmp = ft_strjoin(new_value, value + j);
    free(new_value);
    new_value = tmp;
    free(value);
    free(variable);
    return (new_value);
}

char    *extract_varname(char *str)
{
    char    *tmp;
    char    *extract;
    int i;

    i = 0;
    tmp = malloc(sizeof(char) * 100);
    while (str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '\"')
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    extract = ft_strdup(tmp);
    free(tmp);
    return(extract);
}

char    *expand_variable_dq(char *value)
{
    int i;
    char    *variable;
    char    *var_env;
    
    i = 0;
    while (value[i])
    {
        if (value[i] == '$' && check_in_quote(value, i) != 1)
        {
            i++;
            variable = extract_varname(value + i);
            var_env = getenv(variable);
            value = expand_and_delete(value, variable, var_env);
            i = 0;
            continue ;
        }
        i++;
    }
    return (value);
}
