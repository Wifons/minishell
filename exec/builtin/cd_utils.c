/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:06:45 by wifons            #+#    #+#             */
/*   Updated: 2025/06/20 19:37:59 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *handle_oldpwd(t_shell *sh)
{
	char *path;

	path = env_get(sh->env, "OLDPWD");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (NULL);
	}
	ft_putendl_fd(path, STDERR_FILENO);
	return (path);
}

void print_chdir_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (errno == ENOTDIR)
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
	else if (errno == ENOENT)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
}

void update_pwd_vars(t_shell *sh)
{
	char *old_pwd;
	char *new_pwd;

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