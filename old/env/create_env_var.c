#include "../minishell.h"

char	*create_env_var(char *name, char *value)
{
	char	*var;
	int		len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	var = malloc(len);
	if (!var)
		return (NULL);
	strcpy(var, name);
	strcat(var, "=");
	strcat(var, value);
	return (var);
}
