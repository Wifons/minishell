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

static t_env_var	*add_env_token(const char *str)
{
	t_env_var	*node;
	char	*name;
	char	*val;

	if (parse_env_str(str, &name, &val) != 0)
		return (NULL);
	node = malloc(sizeof(t_env_var));
	node->name = name;
	node->value = val;
	node->next = NULL;
	return (node);
}


t_env_var	*env_init(char **envp)
{
	t_env_var	*env;
	t_env_var	*new_node;
	int						i;

	env = NULL;
	if (!envp)
		return (env);
	i = 0;
	while (envp[i])
	{
		new_node = add_env_token(envp[i]);
		if (!new_node)
		{
			//env_free(env);
			return (NULL);
		}
		ft_lstadd_back_env(&env, new_node);
		i++;
	}
	//print_env(env);
	return (env);
}
