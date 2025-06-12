#include "../minishell.h"

int	env_unset(t_env_var *env, const char *name)
{
	if (!env || !name)
		return (-1);
	ft_lstdelone_if(&env, (void *)name, env_var_cmp_name, env_var_free);
	return (0);
}
