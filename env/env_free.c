#include "../minishell.h"

void	env_var_free(void *var_ptr)
{
	t_env_var *var;

	var = (t_env_var *)var_ptr;
	if (!var)
		return ;
	free(var->name);
	free(var->value);
	free(var);
}

void	env_free(t_env_var *env)
{
	if (!env)
		return ;
	ft_lstclear_env(env);
	free(env);
}
