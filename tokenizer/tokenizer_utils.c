/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 00:41:40 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/15 19:59:14 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_countword(char *str)
{
	int	i;
	int	count;
	int	in_word;
	char	tmp;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] == ' ' && !check_in_quote(str, i))
		{
			in_word = 0;
			i++;
			continue ;
		}
		if (check_symbol(str, i) && !check_in_quote(str, i))
		{
			count++;
			tmp = str[i];
			while (check_symbol(str, i) && str[i] == tmp)
				i++;
			in_word = 0;
			continue ;
		}
		if (in_word == 0)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

char	*ft_strcpy(char *src, char *dest, int debut, int fin)
{
	int	i;

	i = 0;
	while (debut <= fin)
	{
		dest[i] = src[debut];
		i++;
		debut++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*extract_symbol_token(char *str, int *i)
{
	int		start;
	int		tmp;
	char	*token;

	start = *i;
	tmp = str[*i];
	while (check_symbol(str, *i) && str[*i] == tmp)
	{
		(*i)++;
	}
		
	token = (char *)malloc(sizeof(char) * (*i - start + 1));
	token = ft_strcpy(str, token, start, *i - 1);
	return (token);
}

void	ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
}

int	is_quote(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}
