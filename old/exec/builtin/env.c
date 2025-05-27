#include "../../minishell.h"

static int	print_env_vars(t_shell *shell)
{
	int	i;

	if (!shell->env)
		return (GENERAL_ERROR);
	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd(shell->env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (SUCCESS);
}

int	builtin_env(t_shell *shell, t_cmd *cmd)
{
	(void)cmd;
	return (print_env_vars(shell));
}
