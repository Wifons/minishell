/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:05:37 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 17:03:58 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_tildes(t_shell *shell, char *value)
{
	char	*env_var;
	char	*new_value;

	if (ft_strcmp(value, "~") == 0)
	{
		env_var = env_get(shell->env, "HOME");
		free(value);
		if (env_var)
			return (ft_strdup(env_var));
		else
			return (ft_strdup(""));
	}
	if (value[0] == '~' && value[1] == '/')
	{
		env_var = env_get(shell->env, "HOME");
		new_value = ft_strjoin(env_var, (value + 2));
		free(value);
		return (new_value);
	}
	return (value);
}

void	expand_one(t_shell *shell, const char *value, char **exp, int *skip)
{
	if (value[1] == '{')
		expand_brace(shell, value, exp, skip);
	else if (ft_isalpha(value[1]) || value[1] == '_')
		expand_simple(shell, value, exp, skip);
	else if (ft_isdigit(value[1]) != 0)
	{
		*exp = ft_strdup("");
		*skip = 2;
	}
	else
	{
		*exp = ft_strdup("$");
		*skip = 1;
	}
}

void	handle_char(char *value, char **new_value, int *i)
{
	char	tmp[2];

	tmp[0] = value[*i];
	tmp[1] = '\0';
	*new_value = ft_strjoin_free(*new_value, tmp);
	(*i)++;
}

char	*expand_var(t_shell *shell, char *value)
{
	char	*new_value;
	char	*expansion;
	int		skip;
	int		i;

	i = 0;
	new_value = ft_strdup("");
	while (value[i])
	{
		if (value[i] == '$' && check_in_quote(value, i) != 1)
		{
			expand_one(shell, value + i, &expansion, &skip);
			new_value = ft_strjoin_free(new_value, expansion);
			free(expansion);
			i += skip;
		}
		else
			handle_char(value, &new_value, &i);
	}
	free(value);
	return (new_value);
}

void	expansion(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->next->type == WORD)
		{
			tmp = tmp->next;
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->type == WORD)
		{
			tmp->value = expand_tildes(shell, tmp->value);
			tmp->value = expand_var(shell, tmp->value);
			tmp->value = expand_cmd_code(shell, tmp->value);
			tmp->value = translation(tmp->value);
		}
		tmp = tmp->next;
	}
}
