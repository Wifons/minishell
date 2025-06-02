/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:33 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/01 20:36:33 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void exec_cmd(t_shell *sh, t_cmd *cmd, char *path)
{
	char **exec_env;

	exec_env = env_build_arr(sh->env);
	if (!exec_env)
	{
		exec_env = malloc(sizeof(char *));
		if (exec_env)
			exec_env[0] = NULL;
	}
	execve(path, cmd->arguments, exec_env);
	ft_free_array(exec_env);
	perror("execve");
	exit(EXEC_ERROR);
}

static void exec_child(t_shell *shell, t_cmd *cmd, char *path)
{
	if (setup_redirs(cmd) == -1)
		exit(GENERAL_ERROR);
	exec_cmd(shell, cmd, path);
}

static int wait_child(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (GENERAL_ERROR);
}

int exec_external(t_shell *shell, t_cmd *cmd)
{
	pid_t pid;
	char *path;

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
		exec_child(shell, cmd, path);
	free(path);
	return (wait_child(pid));
}
