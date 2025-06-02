/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:10 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/02 21:19:52 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	change_dir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static char	*get_home_path(t_env_manager *env)
{
	char	*path;

	path = env_get(env, "HOME");
	if (!path)
	{
		ft_putstr_fd("Minishell : cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (path);
}

static void	update_pwd_vars(t_shell *sh)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = env_get(sh->env, "PWD");
	if (old_pwd)
		env_set(sh->env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		env_set(sh->env, "PWD", new_pwd);
		free(new_pwd);
	}
}

int	builtin_cd(t_shell *sh, t_cmd *cmd)
{
	char	*path;

	if (!cmd || !cmd->arguments)
		return (-1);
	if (!cmd->arguments[1])
	{
		path = get_home_path(sh->env);
		if (!path)
			return (-1);
	}
	else
		path = cmd->arguments[1];
	if (change_dir(path) == SUCCESS)
	{
		update_pwd_vars(sh);
		return (SUCCESS);
	}
	return (-1);
}
