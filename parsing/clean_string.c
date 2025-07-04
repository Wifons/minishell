/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:14:49 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/20 01:06:06 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\0')
		return (1);
	return (0);
}

char	*ft_clean_comment(char *str)
{
	int		i;
	int		commentaire_position;
	char	*result;

	i = -1;
	commentaire_position = -1;
	while (str[++i])
	{
		if (str[i] == '#' && check_in_quote(str, i) == 0)
		{
			if (i == 0 || is_separator(i - 1))
			{
				commentaire_position = i;
				break ;
			}
		}
	}
	if (commentaire_position == -1)
		commentaire_position = i;
	result = malloc(sizeof(char) * (commentaire_position + 1));
	i = -1;
	while (++i < commentaire_position)
		result[i] = str[i];
	result[i] = '\0';
	return (result);
}

char	*remove_quotes(char *input)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	result = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!result)
		return (NULL);
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	ft_quote(char *str)
{
	int	i;

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
	char	*tmp_char;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->value)
		{
			if (ft_quote(tmp->value))
			{
				tmp_char = remove_quotes(tmp->value);
				free(tmp->value);
				tmp->value = tmp_char;
			}
		}
		tmp = tmp->next;
	}
}
