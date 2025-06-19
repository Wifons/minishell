/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 00:53:25 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 14:36:09 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free (s1);
	return (result);
}

void	expand_simple(t_shell *shell, const char *value, char **exp, int *skip)
{
	int		j;
	char	*variable;
	char	*env_var;

	j = 1;
	while (ft_isalnum(value[j]) || value[j] == '_')
		j++;
	variable = ft_substr(value, 1, j - 1);
	env_var = env_get(shell->env, variable);
	free(variable);
	if (!env_var)
		*exp = ft_strdup("");
	else
		*exp = ft_strdup(env_var);
	*skip = j;
}

void	expand_brace(t_shell *shell, const char *value, char **exp, int *skip)
{
	int		j;
	char	*variable;
	char	*env_var;

	j = 2;
	while (value[j] && value[j] != '}')
		j++;
	variable = ft_substr(value, 2, j - 2);
	env_var = env_get(shell->env, variable);
	free(variable);
	if (!env_var)
		*exp = ft_strdup("");
	else
		*exp = ft_strdup(env_var);
	if (value[j] == '}')
		*skip = j + 1;
	else
		*skip = j;
	return ;
}
