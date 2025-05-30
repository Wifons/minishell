#include "../minishell.h"

int	ft_env_len(char **env)
{
	int	len;

	if (!env)
		return (0);
	len = 0;
	while (env[len])
		len++;
	return (len);
}
