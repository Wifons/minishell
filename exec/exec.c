/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:15 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/02 15:10:21 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_update_underscore(t_shell *sh, t_cmd *cmd)
{
	char	*last_arg;
	int		i;

	if (!sh || !cmd || !cmd->arguments || !cmd->arguments[0])
		return ;
	i = 0;
	while (cmd->arguments[i])
		i++;
	last_arg = cmd->arguments[i - 1];
	env_set(sh->env, "_", last_arg);
}

/* Save current stdin/stdout to restore them later */
static int	save_std_fds(int *stdin_fd, int *stdout_fd)
{
	*stdin_fd = dup(STDIN_FILENO);
	*stdout_fd = dup(STDOUT_FILENO);
	if (*stdin_fd == -1 || *stdout_fd == -1)
		return (-1);
	return (SUCCESS);
}

/* Restore original stdin/stdout after command execution */
static void	restore_std_fds(int stdin_fd, int stdout_fd)
{
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
}

/* Choose between pipeline or single command execution */
static int	choose_exec_mode(t_shell *shell, t_cmd *cmd)
{
	if (count_pipes(cmd) > 0)
		return (exec_pipeline(shell, cmd));
	return (exec_single(shell, cmd));
}

/* Main execution entry point - saves/restores fds and dispatches */
int	exec_command(t_shell *shell, t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	if (!cmd || !cmd->arguments)
		return (SUCCESS);
	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
		return (GENERAL_ERROR);
	env_update_underscore(shell, cmd);
	status = choose_exec_mode(shell, cmd);
	restore_std_fds(saved_stdin, saved_stdout);
	return (status);
}
