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
	int	count = 0;

	if ((str[*i] == '<' && str[*i + 1] == '<') ||
		(str[*i] == '>' && str[*i + 1] == '>') ||
		(str[*i] == '|'&& str[*i + 1] == '|'))
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
int	checking_char(char *str, int *i, int *in_word)
{
	int	count;

	count = 0;
	if (str[*i] == ' ' && !check_in_quote(str, *i))
	{
		*in_word = 0;
		(*i)++;
		return (0);
	}
	if (check_symbol(str, *i) && !check_in_quote(str, *i))
	{
		count += count_symbol_token(str, i);
		*in_word = 0;
		return (count);
	}
	if (*in_word == 0)
	{
		count++;
		*in_word = 1;
	}
	(*i)++;
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

char	*extract_symbol_token(char *str, int *i)
{
	int		start;
	int		tmp;
	int		count_symbol;
	char	*token;

	start = *i;
	tmp = str[*i];
	count_symbol = 0;
	while (check_symbol(str, *i) && str[*i] == tmp)
	{
		(*i)++;
		count_symbol++;
		if (count_symbol == 2)
			break;
	}
	token = (char *)malloc(sizeof(char) * (*i - start + 1));
	token = _ft_strcpy(str, token, start, *i - 1);
	return (token);
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
