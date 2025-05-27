#include "../minishell.h"

static void	free_env_vars(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
}

void	cleanup_env(t_shell *shell)
{
	if (!shell->env)
		return ;
	free_env_vars(shell->env);
	free(shell->env);
	shell->env = NULL;
}
