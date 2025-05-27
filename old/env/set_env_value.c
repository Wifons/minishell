#include "../minishell.h"

static int	update_existing_var(t_shell *shell, int idx, char *new_var)
{
	free(shell->env[idx]);
	shell->env[idx] = new_var;
	return (SUCCESS);
}

static int	add_new_var(t_shell *shell, char *new_var)
{
	int	count;

	count = count_env_vars(shell->env);
	shell->env = resize_env(shell, count + 1);
	if (!shell->env)
		return (GENERAL_ERROR);
	shell->env[count] = new_var;
	return (SUCCESS);
}

int	set_env_value(t_shell *shell, char *name, char *value)
{
	char	*new_var;
	int		idx;
	
	new_var = create_env_var(name, value);
	if (!new_var)
		return (GENERAL_ERROR);
	idx = find_env_var(shell, name);
	if (idx != -1)
		return (update_existing_var(shell, idx, new_var));
	return (add_new_var(shell, new_var));
}
