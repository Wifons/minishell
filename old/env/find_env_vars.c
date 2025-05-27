#include "../minishell.h"

int	find_env_var(t_shell *shell, char *name)
{
	int	i;
	int	len;

	if (!shell->env || !name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0 && shell->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
