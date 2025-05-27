#include "../../minishell.h"

/* Dispatch to the correct builtin function */
int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;

	name = cmd->arguments[0];
	if (ft_strcmp(name, "echo") == 0)
		return (builtin_echo(shell, cmd));
	if (ft_strcmp(name, "cd") == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strcmp(name, "env") == 0)
		return (builtin_env(shell, cmd));
	if (ft_strcmp(name, "export") == 0)
		return (builtin_export(shell, cmd));
	return (GENERAL_ERROR);
}
