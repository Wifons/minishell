/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:58:31 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 21:01:59 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (!path || !*path)
		return (0);
	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

int	print_dir_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": Is a directory", STDERR_FILENO);
	return (126);
}

void	exec_cmd(t_shell *sh, t_cmd *cmd, char *path)
{
	char	**exec_env;

	exec_env = env_build_arr(sh->env);
	if (!exec_env)
	{
		exec_env = malloc(sizeof(char *));
		if (exec_env)
			exec_env[0] = NULL;
	}
	execve(path, cmd->arguments, exec_env);
	ft_free_array(exec_env);
	exit(EXEC_ERROR);
}

void	exec_child(t_shell *shell, t_cmd *cmd, char *path)
{
	if (setup_redirs(cmd) == -1)
		exit(GENERAL_ERROR);
	exec_cmd(shell, cmd, path);
}

int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (GENERAL_ERROR);
}
