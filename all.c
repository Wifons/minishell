#include "../minishell.h"

char	**ft_env_dup(char **env)
{
	char	**copy;
	int		len;
	int		i;

	len = ft_env_len(env);
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			ft_free_array(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
#include "../minishell.h"

static int count_with_values(char **env)
{
	int count = 0;
	int i = 0;

	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			count++;
		i++;
	}
	return (count);
}

static int copy_valued_entries(char **src, char **dst)
{
	int i = 0;
	int j = 0;

	while (src[i])
	{
		if (ft_strchr(src[i], '='))
		{
			dst[j] = ft_strdup(src[i]);
			if (!dst[j])
				return (-1);
			j++;
		}
		i++;
	}
	dst[j] = NULL;
	return (0);
}

char **env_filter(char **env)
{
	char **filtered;
	int count;

	if (!env)
		return (NULL);
	count = count_with_values(env);
	filtered = malloc(sizeof(char *) * (count + 1));
	if (!filtered)
		return (NULL);
	if (copy_valued_entries(env, filtered) == -1)
	{
		ft_free_array(filtered);
		return (NULL);
	}
	return (filtered);
}
#include "../minishell.h"

int	ft_env_find(char **env, const char *name)
{
	int	i;
	int	name_len;

	if (!env || !name)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0)
		{
			if (env[i][name_len] == '=' || env[i][name_len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}
#include "../minishell.h"

char	*ft_env_get(char **env, char *name)
{
	int		idx;
	char	*eq;

	idx = ft_env_find(env, name);
	if (idx == -1)
		return (NULL);
	eq = ft_strchr(env[idx], '=');
	if (!eq)
		return (NULL);
	return (eq + 1);
}
#include "../minishell.h"

int	ft_env_len(char **env)
{
	int	len;

	if (!env)
		return (0);
	len = 0;
	while (env[len])
		len++;
	return (len);
}
#include "../minishell.h"

static char *get_cwd_safe(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("/"));
	return (cwd);
}

static char *calc_next_shlvl(char **env)
{
	char *curr;
	int lvl;

	curr = ft_env_get(env, "SHLVL");
	lvl = 1;
	if (curr)
		lvl = ft_atoi(curr) + 1;
	return (ft_itoa(lvl));
}

static int set_shell_vars(char ***env)
{
	char *cwd;
	char *shlvl;
	int status = 0;

	cwd = get_cwd_safe();
	shlvl = calc_next_shlvl(*env);
	if (!cwd || !shlvl)
		status = -1;
	if (status == 0 && ft_env_set(env, "PWD", cwd) == -1)
		status = -1;
	if (status == 0 && ft_env_set(env, "SHLVL", shlvl) == -1)
		status = -1;
	free(cwd);
	free(shlvl);
	return (status);
}

static int init_oldpwd(char ***env)
{
	if (!ft_env_get(*env, "OLDPWD"))
		return (ft_env_set(env, "OLDPWD", NULL));
	return (0);
}

int env_refresh(char ***env)
{
	if (set_shell_vars(env) == -1)
		return (-1);
	if (init_oldpwd(env) == -1)
		return (-1);
	return (0);
}
#include "../minishell.h"

int ft_env_remove(char ***env, char *name)
{
	int i;
	int j;
	int len;
	char **new_env;

	i = ft_env_find(*env, name);
	if (i == -1)
		return (SUCCESS);
	len = ft_env_len(*env);
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (-1);
	j = 0;
	while (j < len - 1)
	{
		if (j < i)
			new_env[j] = (*env)[j];
		else
			new_env[j] = (*env)[j + 1];
		j++;
	}
	new_env[j] = NULL;
	free((*env)[i]);
	free(*env);
	*env = new_env;
	return (SUCCESS);
}
#include "../minishell.h"

static char *create_env_entry(char *name, char *value)
{
	char *entry;
	int total_len;
	int name_len;
	int value_len;

	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	value_len = 0;
	if (value)
		value_len = ft_strlen(value);
	total_len = name_len + value_len + 2;
	entry = malloc(total_len);
	if (!entry)
		return (NULL);
	strcpy(entry, name);
	if (value)
	{
		strcat(entry, "=");
		strcat(entry, value);
	}
	return (entry);
}

static int ft_env_update_at(char ***env, int idx, char *name, char *value)
{
	char *new_entry;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (-1);
	free((*env)[idx]);
	(*env)[idx] = new_entry;
	return (0);
}

static int ft_env_add_new(char ***env, char *name, char *value)
{
	char **new_env;
	char *new_entry;
	int env_len;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (-1);
	env_len = ft_env_len(*env);
	new_env = realloc(*env, sizeof(char *) * (env_len + 2));
	if (!new_env)
	{
		free(new_entry);
		return (-1);
	}
	new_env[env_len] = new_entry;
	new_env[env_len + 1] = NULL;
	*env = new_env;
	return (0);
}

int is_valid_env_name(char *name)
{
	int i;

	if (!name || !name[0] || ft_isdigit(name[0]))
		return (0);
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int ft_env_set(char ***env, char *name, char *value)
{
	int idx;

	if (!env || !*env || !is_valid_env_name(name))
		return (-1);
	idx = ft_env_find(*env, name);
	if (idx != -1)
		return (ft_env_update_at(env, idx, name, value));
	return (ft_env_add_new(env, name, value));
}
#include "../minishell.h"

static int	env_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '=' && s2[i] != '=')
		return (-1);
	if (s1[i] != '=' && s2[i] == '=')
		return (1);
	return (s1[i] - s2[i]);
}

static void	ft_env_sort(char **env)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = ft_env_len(env);
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (env_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**ft_env_dup_sort(char **env)
{
	char	**sorted_copy;

	sorted_copy = ft_env_dup(env);
	if (!sorted_copy)
		return (NULL);
	ft_env_sort(sorted_copy);
	return (sorted_copy);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:10 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/29 20:39:50 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	change_dir(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static char	*get_home_path(char **env)
{
	char	*path;

	path = ft_env_get(env, "HOME");
	if (!path)
	{
		ft_putstr_fd("Minishell : cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (path);
}

static void	update_pwd_vars(t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_env_get(shell->envp, "PWD");
	if (old_pwd)
		ft_env_set(&shell->envp, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		ft_env_set(&shell->envp, "PWD", new_pwd);
		free(new_pwd);
	}
}

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (!cmd || !cmd->arguments)
		return (-1);
	if (!cmd->arguments[1])
	{
		path = get_home_path(shell->envp);
		if (!path)
			return (-1);
	}
	else
		path = cmd->arguments[1];
	if (change_dir(path) == SUCCESS)
	{
		update_pwd_vars(shell);
		return (SUCCESS);
	}
	return (-1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:15 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:16 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	print_args(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

int	builtin_echo(t_cmd *cmd)
{
	int		i;
	bool	newline;

	if (!cmd || !cmd->arguments)
		return (GENERAL_ERROR);
	i = 1;
	newline = true;
	while (cmd->arguments[i] && is_n_flag(cmd->arguments[i]))
	{
		newline = false;
		i++;
	}
	print_args(cmd->arguments, i);
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
#include "../../minishell.h"

int	builtin_env(t_shell *shell, char **args)
{
	int	i;

	if (args[1])
	{
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
		return (-1);
	}
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
			ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
		i++;
	}
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:19 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/29 19:48:11 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Dispatch to the correct builtin function */
int exec_builtin(t_shell *shell, t_cmd *cmd)
{
	char *name;

	name = cmd->arguments[0];
	if (ft_strcmp(name, "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(name, "cd") == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strcmp(name, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(name, "export") == 0)
		return (builtin_export(shell, cmd->arguments));
	if (ft_strcmp(name, "unset") == 0)
		return (builtin_unset(shell, cmd->arguments));
	if (ft_strcmp(name, "env") == 0)
		return (builtin_env(shell, cmd->arguments));
	if (ft_strcmp(name, "exit") == 0)
		return (builtin_exit(shell, cmd->arguments));
	return (GENERAL_ERROR);
}
#include "../../minishell.h"

/* Check if string is numeric */
static int is_numeric(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Exit shell with status code */
int builtin_exit(t_shell *shell, char **args)
{
	int code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
		exit(SUCCESS);
	if (!is_numeric(args[1]))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit(2);
	}
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (GENERAL_ERROR);
	}
	code = ft_atoi(args[1]);
	ft_free_array(shell->envp);
	exit(code);
}
#include "../../minishell.h"

static void	print_entry(char *entry)
{
	char	*eq;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	eq = ft_strchr(entry, '=');
	if (!eq)
		ft_putendl_fd(entry, STDOUT_FILENO);
	else
	{
		write(STDOUT_FILENO, entry, eq - entry);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(eq + 1, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
}

static int	print_all(char **env)
{
	char	**sorted;
	int		i;

	sorted = ft_env_dup_sort(env);
	if (!sorted)
		return (-1);
	i = 0;
	while (sorted[i])
	{
		print_entry(sorted[i]);
		i++;
	}
	ft_free_array(sorted);
	return (0);
}

static int	export_var(char ***env, char *arg)
{
	char	*eq;
	char	*name;
	int		res;

	eq = ft_strchr(arg, '=');
	name = arg;
	if (eq)
		name = ft_substr(arg, 0, eq - arg);
	if (!name || !is_valid_env_name(name))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		if (name != arg)
			free(name);
		return (-1);
	}
	if (!eq)
	{
		if (name != arg)
			free(name);
		return (SUCCESS);
	}
	res = ft_env_set(env, name, eq + 1);
	free(name);
	return (res);
}

int	builtin_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	if (!args[1])
		return (print_all(shell->envp));
	status = SUCCESS;
	i = 1;
	while (args[i])
	{
		if (export_var(&shell->envp, args[i]) == -1)
			status = -1;
		i++;
	}
	return (status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:23 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/29 19:35:14 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Checks if command is a minishell builtin (echo, cd, pwd, etc)*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
  return (ft_strcmp(cmd, "echo") == 0
        || ft_strcmp(cmd, "cd") == 0
        || ft_strcmp(cmd, "pwd") == 0
        || ft_strcmp(cmd, "export") == 0
        || ft_strcmp(cmd, "unset") == 0
        || ft_strcmp(cmd, "env") == 0
        || ft_strcmp(cmd, "exit") == 0);
}
#include "../../minishell.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (GENERAL_ERROR);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (SUCCESS);
}
#include "../../minishell.h"

int builtin_unset(t_shell *shell, char **args)
{
	int i;

	if (!args[1])
		return (SUCCESS);
	i = 1;
	while (args[i])
	{
		ft_env_remove(&shell->envp, args[i]);
		i++;
	}
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:15 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/28 22:18:01 by wifons           ###   ########.fr       */
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
	status = choose_exec_mode(shell, cmd);
	restore_std_fds(saved_stdin, saved_stdout);
	return (status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:10 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/29 15:51:12 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Execute builtin with redirections setup */
static int	exec_builtin_with_redir(t_shell *shell, t_cmd *cmd)
{
	if (setup_redirs(cmd) == -1)
		return (GENERAL_ERROR);
	return (exec_builtin(shell, cmd));
}

/* Execute a single command (no pipes) - builtin or external */
int	exec_single(t_shell *shell, t_cmd *cmd)
{
	if (is_builtin(cmd->arguments[0]))
		return (exec_builtin_with_redir(shell, cmd));
	return (exec_external(shell, cmd));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:28 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:29 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_cmd_not_found(const char *cmd)
{
	ft_putstr_fd("Minishell : ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:33 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/29 19:32:00 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void exec_cmd(t_shell *sh, t_cmd *cmd, char *path)
{
	char **exec_env;

	exec_env = env_filter(sh->envp);
	if (!exec_env)
		exec_env = sh->envp;
	execve(path, cmd->arguments, exec_env);
	if (exec_env != sh->envp)
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:39 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:40 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Build full path by joining directory and command */
static char	*build_full_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

/* Search for command in PATH directories */
static char	*check_in_path(char **paths, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (full_path && access(full_path, F_OK) == 0)
		{
			ft_free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

/* Find executable path for command (check PATH env var) */
char	*find_cmd_path(const char *cmd)
{
	char	*path_env;
	char	**paths;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (check_in_path(paths, cmd));
}
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:46 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/29 16:44:01 by wifons           ###   ########.fr       */
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
static void	exec_cmd_type(t_shell *shell, t_cmd *cmd)
{
	if (is_builtin(cmd->arguments[0]))
		exit(exec_builtin(shell, cmd));
	else
		exec_external(shell, cmd);
}

/* Setup pipes and execute command in child process */
void	exec_pipe_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2])
{
	setup_pipe_input(in_fd);
	setup_pipe_output(cmd, pipefd);
	exec_cmd_type(shell, cmd);
	exit(SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:51 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:52 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Create a pipe and check for error */
int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (SUCCESS);
}

/* Close both ends of a pipe */
void	close_pipe(int pipefd[2])
{
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
}

/* Count number of pipes in command chain */
int	count_pipes(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		if (cmd->next_pipe)
			count++;
		cmd = cmd->next;
	}
	return (count);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:55 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:07:56 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Redirect stdin to read from pipe */
void	setup_pipe_in(int pipefd[2])
{
	dup2(pipefd[PIPE_READ], STDIN_FILENO);
	close_pipe(pipefd);
}

/* Redirect stdout to write to pipe */
void	setup_pipe_out(int pipefd[2])
{
	dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	close_pipe(pipefd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:07:59 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:08:00 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Duplicate fd to target and close original fd */
int	dup2_close(int fd, int target)
{
	if (dup2(fd, target) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:02 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/26 02:08:03 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Print error message for file operations */
static void	print_file_error(const char *file)
{
	ft_putstr_fd("Minishell : ", STDERR_FILENO);
	perror(file);
}

/* Open file for reading (< file) */
int	open_infile(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_file_error(file);
	return (fd);
}

/* Open file for writing (> file) or appending (>> file) */
int	open_outfile(const char *file, bool append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, FILE_PERMS);
	if (fd == -1)
		print_file_error(file);
	return (fd);
}
#include "../../minishell.h"

static int create_heredoc_pipe(char *heredoc_content)
{
	int pipefd[2];
	pid_t pid;
	int status;
	
	// On crée le pipe
	if (create_pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close_pipe(pipefd);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipefd[PIPE_READ]);
		if (heredoc_content)
			ft_putstr_fd(heredoc_content, pipefd[PIPE_WRITE]);
		close(pipefd[PIPE_WRITE]);
		exit(SUCCESS);
	}
	close(pipefd[PIPE_WRITE]);
	waitpid(pid, &status, 0);
	return (pipefd[PIPE_READ]);
}

int setup_heredoc(t_cmd *cmd)
{
	int heredoc_fd;

	if (!cmd->heredoc_buff)
		return (SUCCESS);
	heredoc_fd = create_heredoc_pipe(cmd->heredoc_buff);
	if (heredoc_fd == -1)
		return (GENERAL_ERROR);
	return (dup2_close(heredoc_fd, STDIN_FILENO));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:08:06 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/27 22:33:01 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Setup input redirection (< file) */
static int	setup_input_redir(const char *file)
{
	int	fd;

	fd = open_infile(file);
	if (fd == -1)
		return (-1);
	return (dup2_close(fd, STDIN_FILENO));
}

/* Setup output redirection (> file) */
static int	setup_output_redir(const char *file)
{
	int	fd;

	fd = open_outfile(file, false);
	if (fd == -1)
		return (-1);
	return (dup2_close(fd, STDOUT_FILENO));
}

/* Setup append redirection (>> file) */
static int	setup_append_redir(const char *file)
{
	int	fd;

	fd = open_outfile(file, true);
	if (fd == -1)
		return (-1);
	return (dup2_close(fd, STDOUT_FILENO));
}

/* Setup all redirections for a command */
int setup_redirs(t_cmd *cmd)
{
	if (cmd->heredoc_buff)
		if (setup_heredoc(cmd) == -1)
			return (-1);
	if (cmd->l_redirect)
		if (setup_input_redir(cmd->l_redirect) == -1)
			return (-1);
	if (cmd->r_redirect)
		if (setup_output_redir(cmd->r_redirect) == -1)
			return (-1);
	if (cmd->app_redirect)
		if (setup_append_redir(cmd->app_redirect) == -1)
			return (-1);
	return (SUCCESS);
}
#include "../../minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
#include "../../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wifons <wifons@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:24:32 by tcassu            #+#    #+#             */
/*   Updated: 2025/05/29 19:19:11 by wifons           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmd;
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.envp = ft_env_dup(envp);
	env_refresh(&shell.envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		add_history(input);
		if (input)
			tokens = tokenize(input);
		if (tokens)
		{
			cmd = parse_cmd(tokens);
			exec_command(&shell, cmd);
			ft_free_cmd_list(cmd);
		}
	}
	return (0);
}
