#include "../minishell.h"

static void	copy_existing_vars(t_shell *shell, char **new_env, int new_size)
{
	int	i;

	i = 0;
	while (shell->env && shell->env[i] && i < new_size)
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = NULL;
}

char	**resize_env(t_shell *shell, int new_size)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		return (NULL);
	copy_existing_vars(shell, new_env, new_size);
	if (shell->env)
		free(shell->env);
	return (new_env);
}
