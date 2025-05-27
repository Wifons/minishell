/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:14:49 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 23:46:11 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Remplace le # et tout ce qu'il y a deriere dans la ligne de commande recus */
char	*ft_clean_comment(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\0')
			return (str);
		if (str[i] == '#' && check_in_quote(str, i) == 0)
			break ;
		i++;
	}
	result = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '#' && check_in_quote(str, i) == 0)
			break ;
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	free(str);
	return (result);
}

char *remove_quotes(char *input)
{
	char	*result;
	char	quote;
	int i;
	int	j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * ft_strlen(input) + 1);
	while (input[i])
	{
		if ((input[i] == '\"' || input[i] == '\'') )
		{
			if (quote == 0)
				quote = input[i];
			else if (input[i] == quote)
				quote = 0;
			else
				result[j++] = input[i];
		}
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	ft_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	clear_quote(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (ft_quote(tmp->value))
			tmp->value = remove_quotes(tmp->value);
		tmp = tmp->next;
	}
}
