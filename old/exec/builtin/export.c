#include "../../minishell.h"

static char	*extract_var_name(char *arg)
{
	char	*equals;
	int		len;
	char	*name;

	equals = ft_strchr(arg, '=');
	if (!equals)
		return (ft_strdup(arg));
	len = equals - arg;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	strncpy(name, arg, len);
	name[len] = '\0';
	return (name);
}

static int	export_single_var(t_shell *shell, char *arg)
{
	char	*name;
	char	*equals;
	int		res;

	name = extract_var_name(arg);
	if (!name)
		return (GENERAL_ERROR);
	equals = ft_strchr(arg, '=');
	if (equals)
		res = set_env_value(shell, name, equals + 1);
	else
		res = SUCCESS;
	free(name);
	return (res);
}

int	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!cmd->arguments[1])
		return (builtin_env(shell, cmd));
	i = 1;
	while (cmd->arguments[i])
	{
		if (export_single_var(shell, cmd->arguments[i]) == GENERAL_ERROR)
			return (GENERAL_ERROR);
		i++;
	}
	return (SUCCESS);
}
