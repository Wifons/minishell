/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:10 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:08:11 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Execute builtin with redirections setup */
static int	exec_builtin_with_redir(t_cmd *cmd)
{
	if (setup_redirs(cmd) == -1)
		return (GENERAL_ERROR);
	return (exec_builtin(cmd));
}

/* Execute a single command (no pipes) - builtin or external */
int	exec_single(t_cmd *cmd)
{
	if (is_builtin(cmd->arguments[0]))
		return (exec_builtin_with_redir(cmd));
	return (exec_external(cmd));
}
