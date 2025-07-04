/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:39 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/20 15:53:57 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Build full path by joining directory and command */
static char *build_full_path(const char *dir, const char *cmd)
{
	char *tmp;
	char *full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

/* Search for command in PATH directories */
static char *check_in_path(char **paths, const char *cmd)
{
	char *full_path;
	int i;

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (full_path && access(full_path, F_OK) == 0)
		{
			ft_free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

static char *check_curr_dir(const char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

/* Find executable path for command (check PATH env var) */
char *find_cmd_path(t_env_var *env, const char *cmd)
{
	char *path_env;
	char **paths;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path_env = env_get(env, "PATH");
	if (!path_env)
		return (check_curr_dir(cmd));
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (check_in_path(paths, cmd));
}
