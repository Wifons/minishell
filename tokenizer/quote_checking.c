/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:48:59 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/20 00:05:22 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_update(int *single_quote, int *double_quote, char value)
{
	if (value == '"')
	{
		if (*double_quote == 0)
			*double_quote = 1;
		else
			*double_quote = 0;
	}
	else
	{
		if (*single_quote == 0 && *double_quote == 0)
			*single_quote = 1;
		else
			*single_quote = 0;
	}
}

int	check_in_quote(char *str, int i)
{
	int	j;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '"' || str[j] == '\'')
			quote_update(&single_quote, &double_quote, str[j]);
		if (j == i)
		{
			if (single_quote)
				return (1);
			if (double_quote)
				return (2);
			return (0);
		}
		j++;
	}
	return (0);
}

int	check_symbol(char *str, int i)
{
	char	*symbol;
	int		j;

	symbol = "&<>|()";
	j = 0;
	while (symbol[j])
	{
		if (str[i] == symbol[j])
			return (1);
		j++;
	}
	return (0);
}
