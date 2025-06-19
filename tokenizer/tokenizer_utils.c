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

int	count_symbol_token(char *str, int *i)
{
	int	count;

	count = 0;
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '|' && str[*i + 1] == '|'))
	{
		count++;
		*i += 2;
	}
	else
	{
		count++;
		(*i)++;
	}
	return (count);
}

int	ft_countword_ms(char *str)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		count += checking_char(str, &i, &in_word);
	}
	return (count);
}

char	*_ft_strcpy(char *src, char *dest, int debut, int fin)
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

void	_ft_free(char **result)
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
