/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:10 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/13 00:17:17 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Execute builtin with redirections setup */
static int	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	if (setup_redirs(cmd) == -1)
		return (GENERAL_ERROR);
	return (exec_builtin(shell, cmd));
}

/* Execute a single command (no pipes) - builtin or external */
int	exec_single(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		return (1);
	if (!cmd->arguments)
	{
		if (setup_redirs(cmd) == -1)
			return (1);
		return (0);
	}
	if (!cmd->arguments[0])
	{
		if (setup_redirs(cmd) == -1)
			return (1);
		return (0);
	}
	if (is_builtin(cmd->arguments[0]))
		return (exec_builtin_with_redir(shell, cmd));
	return (exec_external(shell, cmd));
}
