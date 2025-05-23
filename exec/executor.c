#include "../minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

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

int execute_builtin(t_cmd *cmd)
{
	char *name;

	name = cmd->arguments[0];
	if (ft_strcmp(name, "echo") == 0)
		return (builtin_echo(cmd));
	// if (ft_strcmp(name, "cd") == 0)
	// 	return (builtin_cd(cmd->arguments));
	// if (ft_strcmp(name, "pwd") == 0)
	// 	return (builtin_pwd(cmd->arguments));
	// if (ft_strcmp(name, "export") == 0)
	// 	return (builtin_export(cmd->arguments));
	// if (ft_strcmp(name, "unset") == 0)
	// 	return (builtin_unset(cmd->arguments));
	// if (ft_strcmp(name, "env") == 0)
	// 	return (builtin_env(cmd->arguments));
	// if (ft_strcmp(name, "exit") == 0)
	// 	return (builtin_exit(cmd->arguments));
	return (1);
}

int execute_command(t_cmd *cmd)
{
	if (!cmd || !cmd->arguments)
		return (0);
	if (is_builtin(cmd->arguments[0]))
		return (execute_builtin(cmd));
	return (1);
	// else
		// return (execute_external(cmd));
}