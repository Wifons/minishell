#include "../minishell.h"

int	env_var_is_exportable(void *var_ptr)
{
	t_env_var	*var;

	if (!var_ptr)
		return (0);
	var = (t_env_var *)var_ptr;
	if (!var->name)
		return (0);
	if (!var->value)
		return (0);
	if (ft_strcmp(var->name, "_") == 0)
		return (0);
	return (1);
}
