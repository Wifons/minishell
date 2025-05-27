/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:15 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:08:16 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
static int	choose_exec_mode(t_cmd *cmd)
{
	if (count_pipes(cmd) > 0)
		return (exec_pipeline(cmd));
	return (exec_single(cmd));
}

/* Main execution entry point - saves/restores fds and dispatches */
int	exec_command(t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	if (!cmd || !cmd->arguments)
		return (SUCCESS);
	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
		return (GENERAL_ERROR);
	status = choose_exec_mode(cmd);
	restore_std_fds(saved_stdin, saved_stdout);
	return (status);
}
