#include "../minishell.h"

int	env_var_cmp_name(void *var_ptr, void *name_ref)
{
	t_env_var *var;
	char			*name;

	var = (t_env_var *)var_ptr;
	name = (char *)name_ref;
	if (!var || !var->name || !name)
		return (-1);
	return (ft_strcmp(var->name, name));
}

int	env_var_cmp_var(void *var1_ptr, void *var2_ptr)
{
	t_env_var	*var1;
	t_env_var	*var2;

	var1 = (t_env_var *)var1_ptr;
	var2 = (t_env_var *)var2_ptr;
	if (!var1 || !var1->name || !var2 || !var2->name)
		return (0);
	return (ft_strcmp(var1->name, var2->name));
}
