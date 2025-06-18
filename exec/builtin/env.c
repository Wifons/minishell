#include "../../minishell.h"

static int	env_var_is_env_visible(void *var_ptr)
{
	t_env_var	*var;

	if (!var_ptr)
		return (0);
	var = (t_env_var *)var_ptr;
	if (!var || !var->name)
		return (0);
	if (!var->value || var->value[0] == '\0')
		return (0);
	return (1);
}

static void	print_env_var(void *data)
{
	t_env_var	*var;

	if (!env_var_is_env_visible(data))
		return ;
	var = (t_env_var *)data;
	ft_putstr_fd(var->name, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd(var->value, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	builtin_env(t_shell *sh, char **args)
{
	if (!sh || !sh->env)
		return (-1);
	if (args[1])
	{
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
		return (-1);
	}
	ft_lstiter_env(sh->env, print_env_var);
	return (0);
}
