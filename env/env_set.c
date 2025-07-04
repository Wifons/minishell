/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:42:47 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/19 22:12:32 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dup_value(t_env_var	*var, const char	*value)
{
	var->value = ft_strdup(value);
	if (var->value)
		return (1);
	return (0);
}

static	t_env_var	*create_env_var(const char *name, const char *value)
{
	t_env_var	*var;

	if (!name)
		return (NULL);
	var = ft_calloc(1, sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	if (!var->name)
	{
		free(var);
		return (NULL);
	}
	if (value)
	{
		if (!dup_value(var, value))
		{
			free(var->name);
			free(var);
			return (NULL);
		}
	}
	else
		var->value = NULL;
	return (var);
}

static int	update_existing_var(t_env_var *var, const char *value)
{
	char	*new_val;

	if (!var)
		return (-1);
	if (!value)
		return (0);
	free(var->value);
	var->value = NULL;
	new_val = ft_strdup(value);
	if (!new_val)
		return (-1);
	var->value = new_val;
	return (0);
}

int	env_set(t_env_var *env, const char *name, const char *val)
{
	t_env_var		*existing;
	t_env_var		*new_node;

	if (!env || !name)
		return (-1);
	existing = ft_lstfind(env, (void *)name, env_var_cmp_name);
	if (existing)
		return (update_existing_var((t_env_var *)existing, val));
	new_node = create_env_var(name, val);
	if (!new_node)
	{
		ft_lstclear_env(env);
		return (-1);
	}
	ft_lstadd_back_env(&env, new_node);
	return (0);
}
