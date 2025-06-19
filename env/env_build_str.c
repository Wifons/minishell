/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:42:23 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 03:42:25 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_build_str(t_env_var *var)
{
	char	*tmp;
	char	*res;

	if (!var || !var->name)
		return (NULL);
	if (!var->value)
		return (ft_strdup(var->name));
	tmp = ft_strjoin(var->name, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, var->value);
	free(tmp);
	return (res);
}
