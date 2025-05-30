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
