#include "../minishell.h"

char	*env_build_str(t_env_var *var)
{
	char	*tmp;
	char	*res;

	if (!var || !var->name)
		return (NULL);
	if (!var->value)
		return (ft_strdup(var->name));
	tmp = ft_strjoin(var->name, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, var->value);
	free(tmp);
	return (res);
}
