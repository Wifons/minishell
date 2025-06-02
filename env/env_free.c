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

void	env_free(t_list *env)
{
	if (!env)
		return ;
	ft_lstclear(&env, env_var_free);
	free(env);
}
