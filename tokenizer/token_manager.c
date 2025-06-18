/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:16:18 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/17 19:05:20 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(void *content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup((const char *)content);
	token->next = NULL;
	return (token);
}

void	ft_lstadd_backs(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	last = *tokens;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void	add_type(t_token *tokens)
{
	while (tokens)
	{
		tokens->type = get_type(tokens);
		tokens = tokens->next;
	}
}

t_type	get_type(t_token *tokens)
{
	if (tokens->value[0] == '<' && tokens->value[1] == '\0')
		return (L_REDIRECT);
	else if (tokens->value[0] == '>' && tokens->value[1] == '\0')
		return (R_REDIRECT);
	else if (tokens->value[0] == '<' && tokens->value[1] == '<')
		return (HEREDOC);
	else if (tokens->value[0] == '>' && tokens->value[1] == '>')
		return (APP_REDIRECT);
	else if (tokens->value[0] == '(')
		return (START_SUBSHELL);
	else if (tokens->value[0] == ')')
		return (END_SUBSHELL);
	else if (tokens->value[0] == '|')
		return (PIPE);
	return (WORD);
}

t_token	*parse_line(t_shell *shell, char **str)
{
	t_token	*list;
	t_token	*t1;
	int		i;

	i = 0;
	list = NULL;
	while (str[i])
	{
		t1 = create_token(str[i]);
		free(str[i]);
		ft_lstadd_backs(&list, t1);
		i++;
	}
	free(str);
	add_type(list);
	if (parsing(shell, list))
		return (NULL);
	expansion(shell, list);
	clear_quote(list);
	return (list);
}
