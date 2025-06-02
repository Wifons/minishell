#include "../minishell.h"

char	*env_get(t_env_manager *env, const char *name)
{
	t_list		*node;
	t_env_var	*var;

	if (!env || !name)
		return (NULL);
	node = ft_lstfind(env->vars, (void *)name, env_var_cmp_name);
	if (!node)
		return (NULL);
	var = (t_env_var *)node->content;
	return (var->value);
}
