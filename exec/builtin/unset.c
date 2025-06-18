#include "../../minishell.h"

int builtin_unset(t_shell *sh, char **args)
{
	int	i;

	if (!sh || !sh->env)
		return (-1);
	if (!args[1])
		return (0);
	if (args[1][0] == '-')
	{
		ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
		return (2);
	}
	i = 1;
	while (args[i])
	{
		env_unset(sh->env, args[i]);
		i++;
	}
	return (0);
}
