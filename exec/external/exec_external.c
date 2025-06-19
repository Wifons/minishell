/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:33 by tcassu            #+#    #+#             */
/*   Updated: 2025/06/18 21:02:15 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	print_no_such_file(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (127);
}

static int	validate_path_command(char *cmd_path)
{
	if (access(cmd_path, F_OK) != 0)
		return (print_no_such_file(cmd_path));
	if (is_directory(cmd_path))
		return (print_dir_error(cmd_path));
	if (access(cmd_path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (126);
	}
	return (0);
}

static char	*get_executable_path(t_shell *shell, char *cmd_name
	, int *error_code)
{
	char	*path;

	*error_code = 0;
	if (strchr(cmd_name, '/'))
	{
		*error_code = validate_path_command(cmd_name);
		if (*error_code != 0)
			return (NULL);
		return (ft_strdup(cmd_name));
	}
	path = find_cmd_path(shell->env, cmd_name);
	if (!path || cmd_name[0] == '\0')
	{
		*error_code = print_cmd_not_found(cmd_name);
		if (path)
			free(path);
		return (NULL);
	}
	if (is_directory(path))
	{
		*error_code = print_dir_error(cmd_name);
		free(path);
		return (NULL);
	}
	return (path);
}

static int	fork_and_execute(t_shell *shell, t_cmd *cmd, char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (GENERAL_ERROR);
	}
	if (pid == 0)
	{
		exec_child(shell, cmd, path);
	}
	return (wait_child(pid));
}

int	exec_external(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	int		error_code;
	int		exit_status;

	if (!cmd->arguments[0])
		return (0);
	path = get_executable_path(shell, cmd->arguments[0], &error_code);
	if (!path)
		return (error_code);
	exit_status = fork_and_execute(shell, cmd, path);
	free(path);
	return (exit_status);
}
