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
	{
		env_free(shell->env);
		exit(SUCCESS);
	}
	if (!is_numeric(args[1]))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		env_free(shell->env);
		exit(2);
	}
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (GENERAL_ERROR);
	}
	code = ft_atoi(args[1]);
	env_free(shell->env);
	exit(code);
}
