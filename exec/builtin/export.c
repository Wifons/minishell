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
		res = ft_env_set(env, name, NULL);
		if (name != arg)
			free(name);
		return (res);
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
