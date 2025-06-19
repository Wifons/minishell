/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:32:50 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:38:58 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_free_parse_cmd(t_parse_cmd *parse, t_cmd *result)
{
	free(parse->cmd);
	free(parse->head_cmd);
	free(parse->tmp);
	if (result)
		return (result);
	else
		return (NULL);
}

void	ft_print_error_quote(int singleQ, int doubleQ)
{
	if (singleQ % 2 != 0)
		printf("minishell: unexpected EOF while looking for matching `\''\n");
	else if (doubleQ % 2 != 0)
		printf("minishell: unexpected EOF while looking for matching `\"'\n");
}

int	ft_count_quote(t_shell *shell, char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote % 2 == 0)
			single_quote++;
		if (str[i] == '\"' && single_quote % 2 == 0)
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
	{
		ft_print_error_quote(single_quote, double_quote);
		shell->global_status = 130;
		return (1);
	}
	return (0);
}

int	syntax_error(t_shell *shell, const char *value)
{
	printf("minishell: syntax error near unexpected token `%s'\n", value);
	shell->global_status = 2;
	return (1);
}

int	error_parse(t_cmd **head_cmd, t_token *tokens, t_shell *shell)
{
	ft_free_cmd_list(*head_cmd);
	ft_free_token_list(tokens);
	shell->global_status = 1;
	return (0);
}
