#include "../minishell.h"

static int	parse_env_str(const char *str, char **name, char **val)
{
	char		*eq;
	size_t	len;

	eq = ft_strchr(str, '=');
	if (!eq)
	{
		*name = ft_strdup(str);
		*val = NULL;
		if (!*name)
			return (-1);
		return (0);
	}
	len = eq - str;
	*name = ft_substr(str, 0, len);
	if (!*name)
		return (-1);
	*val = ft_strdup(eq + 1);
	if (!*val)
	{
		free(*name);
		return (-1);
	}
	return (0);
}

static int	add_env_str(t_list *env, const char *str)
{
	char	*name;
	char	*val;
	int		res;

	if (parse_env_str(str, &name, &val) != 0)
		return (-1);
	res = env_set(env, name, val);
	free(name);
	free(val);
	return (res);
}

t_list	*env_init(char **envp)
{
	t_list	*env;
	int						i;

	env = malloc(sizeof(t_list));
	if (!env)
		return (NULL);
	if (!envp)
		return (env);
	i = 0;
	while (envp[i])
	{
		if (add_env_str(env, envp[i]) != 0)
		{
			env_free(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
