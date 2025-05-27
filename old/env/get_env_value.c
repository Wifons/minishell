#include "../minishell.h"

char	*get_env_value(t_shell *shell, char *name)
{
	int	idx;

	idx = find_env_var(shell, name);
	if (idx == -1)
		return (NULL);
	return (shell->env[idx] + ft_strlen(name) + 1);
}
