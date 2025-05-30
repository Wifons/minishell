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
