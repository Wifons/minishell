/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:10 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:11 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	change_dir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("Minishell : cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (GENERAL_ERROR);
	}
	return (SUCCESS);
}

static char	*get_home_path(void)
{
	char	*path;

	path = getenv("HOME");
	if (!path)
	{
		ft_putstr_fd("Minishell : cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (path);
}

int	builtin_cd(t_cmd *cmd)
{
	char	*path;

	if (!cmd || !cmd->arguments)
		return (GENERAL_ERROR);
	if (!cmd->arguments[1])
	{
		path = get_home_path();
		if (!path)
			return (GENERAL_ERROR);
	}
	else
		path = cmd->arguments[1];
	return (change_dir(path));
}
