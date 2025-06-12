/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:05:37 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/11 01:44:08 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    expansion(t_shell *shell, t_token *tokens)
{
    t_token *tmp;
    
    tmp = tokens;
    while(tmp)
    {
        if (tmp->type == WORD)
            tmp->value = expand_variable_dq(shell, tmp->value);
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
    while (value[i] != '$' && value[i])
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
int is_valid_var(const char *str, int i)
{
    if (ft_isalnum(str[i]) || str[i] == '_')
        return (1);
    return (0);
}
char    *extract_varname(char *str)
{
    char    *tmp;
    char    *extract;
    int i;

    i = 0;
    tmp = malloc(sizeof(char) * 100);
    if (ft_isdigit(str[i]))
    {
        tmp[0] = str[i];
        tmp[1] = '\0';
        extract = ft_strdup(tmp);
        free(tmp);
        return (extract);
    }
    while (str[i] != '\0' && is_valid_var(str, i))
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    extract = ft_strdup(tmp);
    free(tmp);
    return(extract);
}
char    *fix_value(char *str)
{
    char    *new_value;
    int i;
    int j;
    
    i = 1;
    j = 0;
    new_value = NULL;
    if (str[i] != '\0')
    {
        new_value = malloc((sizeof(char)) * ft_strlen(str + i) + 1);
        while (str[i] != '\0')
            new_value[j++] = str[i++];
        new_value[j] = '\0';
        free(str);
    }
    return (new_value);
}
char    *expand_variable_dq(t_shell *shell, char *value)
{
    int i;
    char    *variable;
    char    *var_env;
    
    i = 0;
    while (value[i])
    {
        if (value[i] == '$' && value[i + 1] == '?')
        {
            i++;
            variable = ft_strdup("?\0");
            var_env = ft_itoa(shell->global_status);
            value = expand_and_delete(value, variable, var_env);
            free(var_env);
            i = 0;
            continue ;
        }
        else if (value[i] == '$' && (value[i + 1] == '\"' || value[i + 1] == '\''))
        {
            value = fix_value(value);
        }
        else if (value[i] == '$' && value[i + 1] != '\0'
            && check_in_quote(value, i) != 1 && is_valid_var(value, i + 1))
        {
            i++;
            variable = extract_varname(value + i);
            var_env = env_get(shell->env, variable);
            value = expand_and_delete(value, variable, var_env);
            i = 0;
            continue ;
        }
        i++;
    }
    return (value);
}
