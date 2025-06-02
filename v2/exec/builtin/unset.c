#include "../../minishell.h"

int builtin_unset(t_shell *sh, char **args)
{
	int	i;

	if (!sh || !sh->env)
		return (-1);
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		env_unset(sh->env, args[i]);
		i++;
	}
	return (0);
}
