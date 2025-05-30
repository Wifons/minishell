#include "../minishell.h"

char	*ft_env_get(char **env, char *name)
{
	int		idx;
	char	*eq;

	idx = ft_env_find(env, name);
	if (idx == -1)
		return (NULL);
	eq = ft_strchr(env[idx], '=');
	if (!eq)
		return (NULL);
	return (eq + 1);
}
