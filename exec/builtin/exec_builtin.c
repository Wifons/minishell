#include "../../minishell.h"

/* Dispatch to the correct builtin function */
int	exec_builtin(t_cmd *cmd)
{
	char	*name;

	name = cmd->arguments[0];
	if (ft_strcmp(name, "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(name, "cd") == 0)
		return (builtin_cd(cmd));
	return (GENERAL_ERROR);
}
