#include "../minishell.h"

int	env_unset(t_env_manager *env, const char *name)
{
	if (!env || !name)
		return (-1);
	ft_lstdelone_if(&env->vars, (void *)name, env_var_cmp_name, env_var_free);
	env->count = ft_lstsize(env->vars);
	return (0);
}
