/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:46:08 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/20 21:03:54 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int extract_name_value(const char *arg, char **name, char **value)
{
	char *eq;
	size_t len;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		*name = ft_strdup(arg);
		*value = NULL;
		if (!*name)
			return (-1);
		return (0);
	}
	len = eq - arg;
	*name = ft_substr(arg, 0, len);
	if (!*name)
		return (-1);
	*value = ft_strdup(eq + 1);
	if (!*value)
	{
		free(*name);
		*name = NULL;
		return (1);
	}
	return (0);
}

static int parse_export_arg(const char *arg, char **name, char **value)
{
	if (!arg || !name || !value)
		return (-1);
	return (extract_name_value(arg, name, value));
}

static int env_is_valid_name(const char *name)
{
	int i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int export_single_var(t_env_var *env, char *arg)
{
	char *name;
	char *value;
	int res;

	res = parse_export_arg(arg, &name, &value);
	if (res != 0)
		return (res);
	if (!env_is_valid_name(name))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		free(name);
		free(value);
		return (1);
	}
	res = env_set(env, name, value);
	free(name);
	free(value);
	return (res);
}

int builtin_export(t_shell *sh, char **args)
{
	int i;
	int status;

	if (!sh || !sh->env)
		return (-1);
	if (!args[1])
		return (print_all_vars(sh->env));
	status = 0;
	i = 1;
	while (args[i])
	{
		if (export_single_var(sh->env, args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
