#include "../minishell.h"

int ft_env_remove(char ***env, char *name)
{
	int i;
	int j;
	int len;
	char **new_env;

	i = ft_env_find(*env, name);
	if (i == -1)
		return (SUCCESS);
	len = ft_env_len(*env);
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (-1);
	j = 0;
	while (j < len - 1)
	{
		if (j < i)
			new_env[j] = (*env)[j];
		else
			new_env[j] = (*env)[j + 1];
		j++;
	}
	new_env[j] = NULL;
	free((*env)[i]);
	free(*env);
	*env = new_env;
	return (SUCCESS);
}
