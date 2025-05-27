#include "../minishell.h"

int	count_env_vars(char **env)
{
	int	count;

	if (!env)
		return (0);
	count = 0;
	while (env[count])
		count++;
	return (count);
}
