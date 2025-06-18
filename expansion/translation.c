/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:11:37 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/17 18:42:34 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_new_size(char	*str)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (str[i])
	{
		if (check_in_quote(str, i) == 0)
        {
            if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			{
                i++;
                continue ;
            }  
        }
		j++;
		i++;
	}
	return (j);
}
char	*translation(char	*value)
{
	int	i;
	int	j;
	char	*new_value;
	int size;
	
	i = 0;
	j = 0;
	size = ft_new_size(value);
	new_value = malloc(sizeof(char) * size + 1);
	while (value[i])
	{
		if (check_in_quote(value, i) == 0)
        {
            if (value[i] == '$' && (value[i + 1] == '\'' || value[i + 1] == '\"'))
			{
                i++;
                continue ;
            }      
        }
        new_value[j++] = value[i++];  
	}
	new_value[j] = '\0';
    free(value);
	return (new_value);
}