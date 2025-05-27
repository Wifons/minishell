/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:33 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:34 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Replace current process with new program */
static void	exec_cmd(t_cmd *cmd, char *path)
{
	execve(path, cmd->arguments, environ);
	perror("execve");
	exit(EXEC_ERROR);
}

/* Child process: setup redirections and execute */
static void	exec_child(t_cmd *cmd, char *path)
{
	if (setup_redirs(cmd) == -1)
		exit(GENERAL_ERROR);
	exec_cmd(cmd, path);
}

/* Wait for child process and get exit status */
static int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (GENERAL_ERROR);
}

/* Execute external command by forking and calling execve */
int	exec_external(t_cmd *cmd)
{
	pid_t	pid;
	char	*path;

	path = find_cmd_path(cmd->arguments[0]);
	if (!path)
	{
		print_cmd_not_found(cmd->arguments[0]);
		return (CMD_NOT_FOUND);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (GENERAL_ERROR);
	}
	if (pid == 0)
		exec_child(cmd, path);
	free(path);
	return (wait_child(pid));
}
