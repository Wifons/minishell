/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:19 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/06 15:12:02 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Dispatch to the correct builtin function */
int exec_builtin(t_shell *shell, t_cmd *cmd)
{
	char *name;

	name = cmd->arguments[0];
	if (ft_strcmp(name, "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(name, "cd") == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strcmp(name, "pwd") == 0)
		return (builtin_pwd(shell, cmd->arguments));
	if (ft_strcmp(name, "export") == 0)
		return (builtin_export(shell, cmd->arguments));
	if (ft_strcmp(name, "unset") == 0)
		return (builtin_unset(shell, cmd->arguments));
	if (ft_strcmp(name, "env") == 0)
		return (builtin_env(shell, cmd->arguments));
	if (ft_strcmp(name, "exit") == 0)
		return (builtin_exit(shell, cmd->arguments));
	return (GENERAL_ERROR);
}
