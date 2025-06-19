/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:46 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 23:59:02 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_pipe_input(int in_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}

/* Setup stdout to next pipe if needed */
static void	setup_pipe_output(t_cmd *cmd, int pipefd[2])
{
	if (cmd->next_pipe)
		setup_pipe_out(pipefd);
	else if (pipefd[PIPE_WRITE] != -1)
		close_pipe(pipefd);
}

/* Execute command based on type (builtin or external) */
static int	exec_cmd_type(t_shell *shell, t_cmd *cmd)
{
	int	exit_code;

	if (!cmd->arguments)
	{
		if (setup_redirs(cmd) == -1)
			return (1);
		return (0);
	}
	if (is_builtin(cmd->arguments[0]))
		exit_code = exec_builtin(shell, cmd);
	else
		exit_code = exec_external(shell, cmd);
	return (exit_code);
}

/* Setup pipes and execute command in child process */
void	exec_pipe_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2])
{
	int	exit_code;

	setup_pipe_input(in_fd);
	setup_pipe_output(cmd, pipefd);
	exit_code = exec_cmd_type(shell, cmd);
	exit(exit_code);
}
