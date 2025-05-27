/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:46 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:47 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Setup stdin from previous pipe if needed */
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
static void	exec_cmd_type(t_cmd *cmd)
{
	if (is_builtin(cmd->arguments[0]))
		exit(exec_builtin(cmd));
	else
		exec_external(cmd);
}

/* Setup pipes and execute command in child process */
void	exec_pipe_cmd(t_cmd *cmd, int in_fd, int pipefd[2])
{
	setup_pipe_input(in_fd);
	setup_pipe_output(cmd, pipefd);
	exec_cmd_type(cmd);
	exit(SUCCESS);
}
