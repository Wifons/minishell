/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_cmd_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:31:34 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 14:36:22 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_cmd_code(char *value, char *code)
{
	char	*result;
	char	tmp[2];
	int		i;

	i = 0;
	result = ft_strdup("");
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			result = ft_strjoin_free(result, code);
			i += 2;
		}
		else
		{
			tmp[0] = value[i];
			tmp[1] = '\0';
			result = ft_strjoin_free(result, tmp);
			i++;
		}
	}
	return (result);
}

char	*expand_cmd_code(t_shell *shell, char *value)
{
	char	*code;
	char	*result;

	code = ft_itoa(shell->global_status);
	result = replace_cmd_code(value, code);
	free(code);
	free(value);
	return (result);
}
