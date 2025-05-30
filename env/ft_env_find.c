#include "../minishell.h"

int	ft_env_find(char **env, const char *name)
{
	int	i;
	int	name_len;

	if (!env || !name)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0)
		{
			if (env[i][name_len] == '=' || env[i][name_len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}
