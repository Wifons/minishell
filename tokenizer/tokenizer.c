/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:24:12 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:25:35 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			break ;
	}
	token = (char *)malloc(sizeof(char) * (*i - start + 1));
	token = _ft_strcpy(str, token, start, *i - 1);
	return (token);
}

char	*extract_full_token(char *str, int *i)
{
	int		start;
	int		j;
	char	*token;
	char	quote;

	start = *i;
	j = *i;
	while (str[j] && str[j] != ' ' && !check_symbol(str, j))
	{
		if (check_in_quote(str, j))
		{
			quote = str[j];
			j++;
			while (str[j] && str[j] != quote)
				j++;
			if (str[j] == quote)
				j++;
		}
		else
			j++;
	}
	token = (char *)malloc(sizeof(char) * (j - start + 1));
	token = _ft_strcpy(str, token, start, j - 1);
	*i = j;
	return (token);
}

static char	**ft_set_string(char *str, char **result, int *i, int *count)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (!str[*i])
		return (result);
	if (check_symbol(str, *i))
		result[*count] = extract_symbol_token(str, i);
	else
		result[*count] = extract_full_token(str, i);
	(*count)++;
	return (result);
}

t_token	*tokenize(t_shell *shell, char *str)
{
	char	**result;
	int		compteur;
	int		i;

	i = 0;
	compteur = 0;
	if (!str || verif_input(shell, str) || ft_count_quote(shell, str))
		return (NULL);
	str = ft_clean_comment(str);
	result = (char **)malloc(sizeof(char *) * (ft_countword_ms(str) + 1));
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		ft_set_string(str, result, &i, &compteur);
	}
	result[ft_countword_ms(str)] = 0;
	free(str);
	return (parse_line(shell, result));
}
