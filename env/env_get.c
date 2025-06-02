#include "../minishell.h"

char	*env_get(t_list *env, const char *name)
{
	t_list		*node;
	t_env_var	*var;

	if (!env || !name)
		return (NULL);
	node = ft_lstfind(env, (void *)name, env_var_cmp_name);
	if (!node)
		return (NULL);
	var = (t_env_var *)node->content;
	return (var->value);
}
