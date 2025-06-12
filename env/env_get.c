#include "../minishell.h"

char	*env_get(t_env_var *env, const char *name)
{
	t_env_var		*node;

	if (!env || !name)
		return (NULL);
	node = ft_lstfind(env, (void *)name, env_var_cmp_name);
	if (!node)
		return (NULL);
	return (node->value);
}
