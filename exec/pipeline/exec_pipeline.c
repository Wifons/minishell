/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:43 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/28 22:17:29 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Fork a child process for a command in the pipeline */
static int	fork_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exec_pipe_cmd(shell, cmd, in_fd, pipefd);
	return (SUCCESS);
}

/* Update pipe file descriptors for next command */
static void	update_pipe_fd(int *in_fd, int pipefd[2])
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	close(pipefd[PIPE_WRITE]);
	*in_fd = pipefd[PIPE_READ];
}

/* Wait for all child processes and return last exit status */
static int	wait_pipeline(int n_cmds)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < n_cmds)
	{
		wait(&status);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	return (last_status);
}

/* Execute all commands in the pipeline */
static int	exec_loop(t_shell *shell, t_cmd *cmd, int *n_cmds)
{
	int	pipefd[2];
	int	in_fd;

	in_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next_pipe && create_pipe(pipefd) == -1)
			return (GENERAL_ERROR);
		if (fork_cmd(shell, cmd, in_fd, pipefd) == -1)
			return (GENERAL_ERROR);
		if (cmd->next_pipe)
			update_pipe_fd(&in_fd, pipefd);
		else if (in_fd != STDIN_FILENO)
			close(in_fd);
		(*n_cmds)++;
		cmd = cmd->next;
	}
	return (SUCCESS);
}

/* Main pipeline execution - fork all commands and wait */
int	exec_pipeline(t_shell *shell, t_cmd *cmd)
{
	int	n_cmds;

	n_cmds = 0;
	if (exec_loop(shell, cmd, &n_cmds) == GENERAL_ERROR)
		return (GENERAL_ERROR);
	return (wait_pipeline(n_cmds));
}
